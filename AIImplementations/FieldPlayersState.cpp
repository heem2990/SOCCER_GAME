#include "FieldPlayersState.h"
#include "FieldPlayers.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "Teams.h"
#include "SoccerGame.h"
#include <iostream>

// Wait State functions
void Wait::enter( FieldPlayers* pPlayer )
{
   std::cout<<"Entering the Wait state"<<std::endl;
}

void Wait::execute( FieldPlayers* pPlayer )
{
   if( !pPlayer->isAtTarget() )
   {
      pPlayer->getSteeringBehavior()->arriveOn();
      return;
   }
   else
   {
      pPlayer->getSteeringBehavior()->arriveOff();
      pPlayer->setVelocity( glm::vec2( 0, 0 ) );

      // TODO: track ball
   }

   if( pPlayer->getMyTeam()->hasControl() &&
      !pPlayer->isPlayerControllingTheBall() &&
       pPlayer->isPlayerAheadOfAttacker() )
   {
      // TODO request pass
      return;
   }

   if( SoccerGame::getGameInstance()->isGameOn() )
   {
      if( pPlayer->isPlayerClosestToBall() &&
          pPlayer->getMyTeam()->getReceivingPlayer() == NULL &&
          SoccerGame::getGameInstance()->doGoalkeepersHaveBall() ) 
      {
         pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
         return;
      }
   }

}

void Wait::exit( FieldPlayers* pPlayer )
{
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
	pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
	pPlayer->getSteeringBehavior()->seekOn();
}

void ChaseBall::execute( FieldPlayers* pPlayer )
{
	if( pPlayer->isInKickingRangeOfTheBall() )
	{
		pPlayer->getStateMachine()->changeState( KickBall::getInstance() );
		return;
	}

	if( pPlayer->isPlayerClosestToBall() )
	{
		pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
		return;
	}

	pPlayer->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
}

void ChaseBall::exit( FieldPlayers* pPlayer )
{
	pPlayer->getSteeringBehavior()->seekOff();
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

   if( pPlayer->getSteeringBehavior()->isPusuitOn() )
   {
      pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   }

   if( pPlayer->isAtTarget() )
   {
      pPlayer->getSteeringBehavior()->pursuitOff();
      pPlayer->setVelocity( glm::vec2( 0, 0 ) );
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
   /*if( !pPlayer->isPlayerControllingTheBall() )
   {
      pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
   }*/
   // check if player is facing the goal. 
   // if player is not, then make small kicks and rotate the player 
   // if player is facing the opponents goal, kick with max dribble force.

   pPlayer->getStateMachine()->changeState( ChaseBall::getInstance() );
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

}

void KickBall::execute( FieldPlayers* pPlayer )
{
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

   if( pPlayer->isAtTarget() )
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
   if( pPlayer->isAtArriveTarget() ) 
   {
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