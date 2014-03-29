#include "FieldPlayersState.h"
#include "FieldPlayers.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "Teams.h"
#include "SoccerGame.h"
#include <iostream>
#include <stdlib.h>
#include "GoalPosts.h"

// Wait State functions
void Wait::enter( FieldPlayers* pPlayer )
{
   std::cout<<"Entering the Wait state"<<std::endl;
   pPlayer->setHomeRegionAsTarget();
}

void Wait::execute( FieldPlayers* pPlayer )
{
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
       pPlayer->isPlayerAheadOfAttacker() )
   {
      pPlayer->getMyTeam()->requestPass( pPlayer );
      return;
   }

   if( SoccerGame::getGameInstance()->isGameOn() )
   {
      if( pPlayer->isPlayerClosestToBall() &&
          pPlayer->getMyTeam()->getReceivingPlayer() == NULL &&
          !SoccerGame::getGameInstance()->doGoalkeepersHaveBall() ) 
      {
         pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
         return;
      }
   }
}

void Wait::exit( FieldPlayers* pPlayer )
{
   pPlayer->lookAtOff();
   std::cout<<"Exiting the Wait state"<<std::endl;
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
   std::cout<<"Entering Chase Ball "<<std::endl;
	pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pPlayer->getSteeringBehavior()->pursuitOn();
}

void ChaseBall::execute( FieldPlayers* pPlayer )
{
	if( pPlayer->isInKickingRangeOfTheBall() )
	{
      pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
		pPlayer->getStateMachine()->changeState( KickBall::getInstance() );
		return;
	}

	if( pPlayer->isPlayerClosestToBall() )
	{
		pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
		return;
	}

   pPlayer->setHasBall( false );
	pPlayer->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
}

void ChaseBall::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Exiting Chase Ball"<<std::endl;
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
   std::cout<<"Player has entered the Receiving ball state"<<std::endl;
   pPlayer->getMyTeam()->setReceivingPlayer( pPlayer );
   pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );

   // TODO Change behavior depending on the location of the current player, and chances of it getting intercepted. If they are low, use arrive. 
   pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pPlayer->getSteeringBehavior()->pursuitOn();
}

void ReceiveBall::execute( FieldPlayers* pPlayer )
{
   if( pPlayer->isPlayerWithinReceivingRange() || ! pPlayer->getMyTeam()->hasControl() )
   {
      pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );

      return;
   }

   if( pPlayer->getSteeringBehavior()->isPursuitOn() )
   {
      pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   }

   if( pPlayer->isAtTarget() )
   {
      pPlayer->getSteeringBehavior()->pursuitOff();
      pPlayer->setVelocity( glm::vec2( 0, 0 ) );
      pPlayer->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
   }
}

void ReceiveBall::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Player has exited the Receiving ball state"<<std::endl;
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
   std::cout<<"Player entered Dribble state"<<std::endl;
   pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
}

void Dribble::execute( FieldPlayers* pPlayer )
{
   float dot = glm::dot( pPlayer->getMyTeam()->getGoalPost()->getFacing(), pPlayer->getHeading() );

   if( dot < 0 )
   {
      glm::vec2 playerDirection = pPlayer->getHeading();
      float angle = ( 3.1415 / 4 ); // 3.1415 = pi TODO: Change according to whether the player turns clockwise or anticlockwise to be take the smaller turn

      playerDirection = glm::vec2( playerDirection.x * cosf( angle ) - playerDirection.y * sinf( angle ), playerDirection.x * sinf( angle ) + playerDirection.y * cosf( angle ) );

      const float kickingForce = 40.0f;
      SoccerBall::getSoccerBallInstance()->kick( playerDirection,  kickingForce );
   }
   else
   {
      SoccerBall::getSoccerBallInstance()->kick( pPlayer->getMyTeam()->getGoalPost()->getFacing(),  10.0f );
   }

   pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
   return;
}

void Dribble::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Player has exited dribbling state.";
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
   pPlayer->getMyTeam()->setPlayerWithBall( pPlayer );
   pPlayer->setHasBall( true );
   // check how many kicks the player has attempted and change to chase ball if more than allowed attempts. 
   // TODO: Check if the player has just kicked the ball.
}

void KickBall::execute( FieldPlayers* pPlayer )
{
   glm::vec2 toBall = SoccerBall::getSoccerBallInstance()->getPosition() - pPlayer->getPosition();
   float dotWithBall = glm::dot( pPlayer->getHeading(), glm::normalize( toBall ) );

   if( ( pPlayer->getMyTeam()->getReceivingPlayer() != NULL && pPlayer->getMyTeam()->getReceivingPlayer() != pPlayer ) || pPlayer->getMyTeam()->doesGoalKeeperHaveBall() || dotWithBall < 0 )
   {
      pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
      return;
   }

   glm::vec2 ballTarget( 0, 0 );
   float power = 10 * dotWithBall; // TODO: 40 is max force change and make it const. Magic number 

   if( pPlayer->getMyTeam()->canShoot( SoccerBall::getSoccerBallInstance()->getPosition(), power, ballTarget ) || ( ( std::rand() % 10 ) < 1 ) )
   {
      //TODO: Add noise to kick for randomness
      glm::vec2 kickDirection = ballTarget - SoccerBall::getSoccerBallInstance()->getPosition();

      SoccerBall::getSoccerBallInstance()->kick( kickDirection, power );
      pPlayer->getStateMachine()->changeState( Wait::getInstance() );
      pPlayer->setHasBall( false );

      pPlayer->findSupportingPlayer();
      return;
   }
      
   // Check if the player can pass TODO
   pPlayer->getStateMachine()->changeState( Dribble::getInstance() );
   pPlayer->findSupportingPlayer();
   return;
}

void KickBall::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Exiting KickBall state"<<std::endl;
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
   std::cout<<"Player has entered support state.";
   pPlayer->getSteeringBehavior()->arriveOn();
   //get the best support spot and set it as players target. 
}

void SupportPlayerWithBall::execute( FieldPlayers* pPlayer )
{
   if( !pPlayer->getMyTeam()->hasControl() )
   {
      pPlayer->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
      return;
   }

   // if the best support spot changes, change the steering target. 

   // request pass if able to kcik to goal. 

   if( pPlayer->isAtArriveTarget() )
   {
      pPlayer->getSteeringBehavior()->arriveOff();
      // track ball

      pPlayer->setVelocity( glm::vec2( 0, 0 ) );

      // request pass if not threatend by an opposing player. 
   }
}

void SupportPlayerWithBall::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Player exiting support state "<<std::endl;
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
   std::cout<<"Player is returning home"<<std::endl;
   pPlayer->getSteeringBehavior()->arriveOn();
   pPlayer->setHomeRegionAsTarget(); 
}

void FieldPlayerReturnHome::execute( FieldPlayers* pPlayer )
{
   if( pPlayer->isPlayerHome() ) 
   {
      pPlayer->setHasBall( false );
      pPlayer->getStateMachine()->changeState( Wait::getInstance() );
      return;
   }
}

void FieldPlayerReturnHome::exit( FieldPlayers* pPlayer )
{
   std::cout<<"Player exiting FieldPlayerReturnHome state"<<std::endl;
}

FieldPlayerReturnHome* FieldPlayerReturnHome::getInstance()
{
   static FieldPlayerReturnHome returnHomeState;
   return &returnHomeState;
}