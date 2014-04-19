#include "FieldPlayersState.h"
#include "FieldPlayers.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "Teams.h"
#include "SoccerGame.h"
#include <iostream>
#include <stdlib.h>
#include "GoalPosts.h"
#include "MessageDispatcher.h"
#include <allegro5/allegro_primitives.h>

// Wait State functions
void Wait::enter( FieldPlayers* pPlayer )
{
   pPlayer->setHomeRegionAsTarget();
}

void Wait::execute( FieldPlayers* pPlayer )
{
   if( !SoccerGame::getGameInstance()->isGameOn() )
   {
      return;
   }

	if( !pPlayer->isAtArriveTarget() )
   {
      pPlayer->getSteeringBehavior()->arriveOn();
      return;
   }
   else
   {
      pPlayer->getSteeringBehavior()->arriveOff();
      pPlayer->setVelocity( glm::vec2( 0, 0 ) );
	   pPlayer->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
   }

   if( pPlayer->getMyTeam()->hasControl() &&
       pPlayer->isPlayerAheadOfAttacker() &&
       !pPlayer->getMyTeam()->doesGoalKeeperHaveBall() )
   {
      pPlayer->getMyTeam()->requestPass( pPlayer );
      return;
   }

   if( pPlayer->isPlayerClosestToBall() &&
       pPlayer->getMyTeam()->getReceivingPlayer() == NULL &&
       !pPlayer->getMyTeam()->hasControl() &&
       !SoccerGame::getGameInstance()->doGoalkeepersHaveBall() ) 
   {
      pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
      return;
   }

 /*  if( SoccerGame::getGameInstance()->isGameOn() )
   {
   }*/
}

void Wait::exit( FieldPlayers* pPlayer )
{
   pPlayer->lookAtOff();
}

Wait* Wait::getInstance()
{
   static Wait waitState;
   return &waitState;
}

//*****************************************************************
// ChaseBall State functions

void ChaseBall::enter( FieldPlayers* pPlayer )
{
	pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pPlayer->getSteeringBehavior()->pursuitOn();
}

void ChaseBall::execute( FieldPlayers* pPlayer )
{
   if( pPlayer->isPlayerControllingTheBall() && pPlayer->isAtTarget() )
   {
      pPlayer->getStateMachine()->changeState( Dribble::getInstance() );
      return;
   }

	//if( pPlayer->isInKickingRangeOfTheBall() )
	//{
 //     pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );                                                                                                                                                                                                                                                                                                                                  
	//	pPlayer->getStateMachine()->changeState( KickBall::getInstance() );
	//	return;
	//}
 //  else
 //  {
 //     pPlayer->setHasBall( false );
 //  }

	//if( pPlayer->isPlayerClosestToBall() )
	//{
	//	pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
	//	return;
	//}

	////pPlayer->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
}

void ChaseBall::exit( FieldPlayers* pPlayer )
{
	pPlayer->getSteeringBehavior()->pursuitOff();
}

ChaseBall* ChaseBall::getInstance()
{
   static ChaseBall chaseBallState;
   return &chaseBallState;
}

//*****************************************************************
// ReceiveBall State functions

void ReceiveBall::enter( FieldPlayers* pPlayer )
{
 //  pPlayer->getMyTeam()->setReceivingPlayer( pPlayer );

   //// TODO Change behavior depending on the location of the current player, and chances of it getting intercepted. If they are low, use arrive. 
   pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pPlayer->getSteeringBehavior()->pursuitOn();
}

void ReceiveBall::execute( FieldPlayers* pPlayer )
{
   //if( pPlayer->isPlayerWithinReceivingRange() || ! pPlayer->getMyTeam()->hasControl() )
   //{
   //   pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );

   //   return;
   //}

   if( pPlayer->isPlayerWithinReceivingRange() /*&& SoccerGame::getGameInstance()->isGameOn()*/ )
   {
      pPlayer->getSteeringBehavior()->pursuitOff();
      pPlayer->setVelocity( glm::vec2( 0, 0 ) );
      pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
      SoccerBall::getSoccerBallInstance()->trap( pPlayer );
      //pPlayer->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
      pPlayer->getStateMachine()->setCurrentState( Dribble::getInstance() );
   }
}

void ReceiveBall::exit( FieldPlayers* pPlayer )
{
}

ReceiveBall* ReceiveBall::getInstance()
{
   static ReceiveBall receiveBallState;
   return &receiveBallState;
}

//*****************************************************************
// Dribble State functions

void Dribble::enter( FieldPlayers* pPlayer )
{
   pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
}

void Dribble::execute( FieldPlayers* pPlayer )
{
   al_draw_rectangle( pPlayer->getPosition().x, pPlayer->getPosition().y, pPlayer->getPosition().x + 40.0f, pPlayer->getPosition().y + 40.0f, al_map_rgb( 200.0f, 130.0f, 50.0f ), 10.0f );
   float dot = glm::dot( pPlayer->getMyTeam()->getGoalPost()->getFacing(), pPlayer->getHeading() );
   
   if( pPlayer->isThreatened() )
   {
      pPlayer->findSupportingPlayer();
      SoccerBall::getSoccerBallInstance()->kick( pPlayer->getMyTeam()->getSupportingPlayer()->getPosition() - SoccerBall::getSoccerBallInstance()->getPosition(), 100.0f );
      MessageDispatcher::getInstance()->dispatchMessage( 0.0f, pPlayer, pPlayer->getMyTeam()->getSupportingPlayer(), MESSAGE_TYPES::RECEIVE_BALL, &pPlayer->getMyTeam()->getSupportingPlayer()->getPosition() );
      pPlayer->getStateMachine()->changeState( Wait::getInstance() );
      pPlayer->getMyTeam()->setPlayerWithBall( NULL );
      return;   
   }
   
   if( dot < 0 )
   {
      glm::vec2 playerDirection = pPlayer->getHeading();
      float angle = ( 3.1415f / 2.0f ); // 3.1415 = pi TODO: Change according to whether the player turns clockwise or anticlockwise to be take the smaller turn

      playerDirection = glm::vec2( playerDirection.x * cosf( angle ) - playerDirection.y * sinf( angle ), playerDirection.x * sinf( angle ) + playerDirection.y * cosf( angle ) );

      const float kickingForce = 100.0f;
      SoccerBall::getSoccerBallInstance()->kick( playerDirection,  5.0f );
   }
   else
   {
      SoccerBall::getSoccerBallInstance()->kick( pPlayer->getMyTeam()->getGoalPost()->getFacing(),  20.0f );
   }

   if( !pPlayer->getMyTeam()->doesGoalKeeperHaveBall() && SoccerGame::getGameInstance()->isGameOn() )
   {
      pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
   }
   //return;
}

void Dribble::exit( FieldPlayers* pPlayer )
{
   std::cout<<"\n ************** EXITING DRIBBLE *************\n ";
}

Dribble* Dribble::getInstance()
{
   static Dribble dribbleState;
   return &dribbleState;
}

//*****************************************************************
// KickBall State functions

void KickBall::enter( FieldPlayers* pPlayer )
{
   //pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
   //pPlayer->setHasBall( true );
   // check how many kicks the player has attempted and change to chase ball if more than allowed attempts. 
   // TODO: Check if the player has just kicked the ball.
}

void KickBall::execute( FieldPlayers* pPlayer )
{
   //glm::vec2 toBall = SoccerBall::getSoccerBallInstance()->getPosition() - pPlayer->getPosition();
   //float dotWithBall = glm::dot( pPlayer->getHeading(), glm::normalize( toBall ) );

   //if( ( pPlayer->getMyTeam()->getReceivingPlayer() != NULL && pPlayer->getMyTeam()->getReceivingPlayer() != pPlayer ) || pPlayer->getMyTeam()->doesGoalKeeperHaveBall() || dotWithBall < 0 )
   //{
   //   pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
   //   return;
   //}

   //glm::vec2 ballTarget( 0, 0 );
   //float power = 40 * dotWithBall; // TODO: 40 is max force change and make it const. Magic number 

   //if( pPlayer->getMyTeam()->canShoot( SoccerBall::getSoccerBallInstance()->getPosition(), power, ballTarget ) || ( ( std::rand() % 10 ) < 1 ) )
   //{
   //   //TODO: Add noise to kick for randomness
   //   glm::vec2 kickDirection = ballTarget - SoccerBall::getSoccerBallInstance()->getPosition();

   //   SoccerBall::getSoccerBallInstance()->kick( kickDirection, power );
   //   pPlayer->getStateMachine()->changeState( Wait::getInstance() );
   //   pPlayer->setHasBall( false );

   //   pPlayer->findSupportingPlayer();
   //   return;
   //}
   //   
   //// Check if the player can pass TODO
   //pPlayer->getStateMachine()->changeState( Dribble::getInstance() );
   //pPlayer->findSupportingPlayer();
   //return;
}

void KickBall::exit( FieldPlayers* pPlayer )
{
}

KickBall* KickBall::getInstance()
{
   static KickBall kickBallState;
   return &kickBallState;
}

//*****************************************************************
// SupportPlayerWithBall State functions

void SupportPlayerWithBall::enter( FieldPlayers* pPlayer )
{
   pPlayer->getSteeringBehavior()->setArriveTarget( pPlayer->getMyTeam()->getBestSupportSpot() );
   pPlayer->getSteeringBehavior()->arriveOn();
   pPlayer->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
   //get the best support spot and set it as players target. 
}

void SupportPlayerWithBall::execute( FieldPlayers* pPlayer )
{
   if( pPlayer->getMyTeam()->getOpponent()->hasControl() )
   {
      pPlayer->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
      return;
   }

   //// if the best support spot changes, change the steering target. 

   // pPlayer->getSteeringBehavior()->setArriveTarget( pPlayer->getMyTeam()->getBestSupportSpot() );

   //// request pass if able to kcik to goal. 

   if( pPlayer->isAtArriveTarget() )
   {

      pPlayer->getSteeringBehavior()->setArriveTarget( pPlayer->getMyTeam()->getBestSupportSpot() );
      //pPlayer->getSteeringBehavior()->arriveOff();
      // track ball

      //pPlayer->setVelocity( glm::vec2( 0, 0 ) );
      pPlayer->getStateMachine()->setCurrentState( Wait::getInstance() );

     // request pass if not threatend by an opposing player. 
   }
}

void SupportPlayerWithBall::exit( FieldPlayers* pPlayer )
{
   pPlayer->getSteeringBehavior()->arriveOff();
}

SupportPlayerWithBall* SupportPlayerWithBall::getInstance()
{
   static SupportPlayerWithBall supportPlayerState;
   return &supportPlayerState;
}

//*****************************************************************
// ReturnHome State functions

void FieldPlayerReturnHome::enter( FieldPlayers* pPlayer )
{
   pPlayer->setHomeRegionAsTarget(); 
   pPlayer->getSteeringBehavior()->pursuitOff();
   pPlayer->getSteeringBehavior()->interposeOff();
   pPlayer->getSteeringBehavior()->seekOff();

   pPlayer->getSteeringBehavior()->arriveOn();
   pPlayer->setHasBall( false );
}

void FieldPlayerReturnHome::execute( FieldPlayers* pPlayer )
{
   //if( pPlayer->isPlayerClosestToBall() &&
   //    pPlayer->getMyTeam()->getReceivingPlayer() == NULL &&
   //    !SoccerGame::getGameInstance()->doGoalkeepersHaveBall() ) 
   //{
   //   pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
   //   return;
   //}

   if( pPlayer->isPlayerHome() ) 
   {
      //pPlayer->getMyTeam()->setPlayerWithBall( NULL );
      pPlayer->getStateMachine()->changeState( Wait::getInstance() );
      return;
   }
}

void FieldPlayerReturnHome::exit( FieldPlayers* pPlayer )
{
   pPlayer->getSteeringBehavior()->arriveOff();
}

FieldPlayerReturnHome* FieldPlayerReturnHome::getInstance()
{
   static FieldPlayerReturnHome returnHomeState;
   return &returnHomeState;
}