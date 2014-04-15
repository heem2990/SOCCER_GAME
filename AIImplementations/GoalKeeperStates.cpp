#include "GoalKeeperStates.h"
#include "GoalKeeper.h"
#include <iostream>
#include "SteeringBehaviors.h"
#include "Teams.h"
#include "SoccerBall.h"
#include "SoccerGame.h"
#include "GoalPosts.h"
#include "MessageDispatcher.h"

// ReturnHome State functions
void ReturnGoalkeeperHome::enter( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->setHomeRegionAsTarget();
   pGoalKeeper->getSteeringBehavior()->arriveOn();
}

void ReturnGoalkeeperHome::execute( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->setHomeRegionAsTarget();

   if( pGoalKeeper->isPlayerControllingTheBall() )
   {
      SoccerBall::getSoccerBallInstance()->setVelocity( pGoalKeeper->getVelocity() );
      
      if( !SoccerGame::getGameInstance()->isGameOn() && !pGoalKeeper->isPlayerHome() )
      {
         return;
      }
      else
      {
         pGoalKeeper->getStateMachine()->setCurrentState( GoalKick::getInstance() );
         return;
      }
   }
   bool isGameOn = SoccerGame::getGameInstance()->isGameOn();
   bool teamHasControl = pGoalKeeper->getMyTeam()->hasControl();
   bool isGKHome = pGoalKeeper->isPlayerHome();
   if( ( isGKHome || !teamHasControl ) && isGameOn )
   {
      pGoalKeeper->getStateMachine()->changeState( TendGoal::getInstance() );
   }
}

void ReturnGoalkeeperHome::exit( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->arriveOff();
}

ReturnGoalkeeperHome* ReturnGoalkeeperHome::getInstance()
{
   static ReturnGoalkeeperHome returnHomeState;
   return &returnHomeState;
}
 
//*****************************************************************
// TendGoal State functions

void TendGoal::enter( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   glm::vec2 goalCenter = pGoalKeeper->getMyTeam()->getGoalPost()->getCenter() ;
   pGoalKeeper->getSteeringBehavior()->setInterPoseStaticTarget( goalCenter, 0.2 );
   pGoalKeeper->getSteeringBehavior()->interposeOn();
   pGoalKeeper->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
}

void TendGoal::execute( GoalKeeper* pGoalKeeper )
{
   //if( pGoalKeeper->isInKickingRangeOfTheBall() )
   //{
   //   SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
   //   pGoalKeeper->setHasBall( true );
   //   pGoalKeeper->getStateMachine()->changeState( GoalKick::getInstance() );
   //   return;
   //}

   if( pGoalKeeper->isBallWithinInterceptRanger() )
   {
      pGoalKeeper->getStateMachine()->changeState( InterceptBall::getInstance() );
   }

   //if( pGoalKeeper->isTooFarFromGoal() && pGoalKeeper->getMyTeam()->hasControl() )
   //{
   //   pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
   //}
}

void TendGoal::exit( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->interposeOff();
   //pGoalKeeper->lookAtOff();
}

TendGoal* TendGoal::getInstance()
{
   static TendGoal tendGoalState;
   return &tendGoalState;
}

//*****************************************************************
// goalKick State functions

void GoalKick::enter( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getMyTeam()->sendPlayersHome();
   pGoalKeeper->getMyTeam()->getOpponent()->sendPlayersHome();
   pGoalKeeper->getMyTeam()->setPlayerWithBall( pGoalKeeper );
}

void GoalKick::execute( GoalKeeper* pGoalKeeper )
{
   SoccerBall::getSoccerBallInstance()->setVelocity( pGoalKeeper->getVelocity() );
   //Players* passReceivingPlayer = NULL;
   //glm::vec2 passPosition( 0, 0 );
   //if( pGoalKeeper->getMyTeam()->findPass( pGoalKeeper, passReceivingPlayer, passPosition, 30, 10 ) )
   //{
   //   if( passReceivingPlayer )
   //   {
   //      SoccerBall::getSoccerBallInstance()->kick( glm::normalize( passPosition - pGoalKeeper->getPosition() ), 60 );
   //      pGoalKeeper->setHasBall( false );

   //      MessageDispatcher::getInstance()->dispatchMessage( 0,pGoalKeeper,passReceivingPlayer, MESSAGE_TYPES::RECEIVE_BALL, &passPosition );
   //      pGoalKeeper->setHasBall( false );
   //      pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
   //      return;
   //   }
   //}
   //SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
}

void GoalKick::exit( GoalKeeper* pGoalKeeper )
{
}

GoalKick* GoalKick::getInstance()
{
   static GoalKick goalKickState;
   return &goalKickState;
}

//*****************************************************************
// InterceptBall State functions

void InterceptBall::enter( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pGoalKeeper->getSteeringBehavior()->pursuitOn();
}

void InterceptBall::execute( GoalKeeper* pGoalKeeper )
{
   //if( pGoalKeeper->isTooFarFromGoal() && !pGoalKeeper->isPlayerClosestToBall() )
   //{
   //   pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
   //   return;
   //}
   if( pGoalKeeper->isInKickingRangeOfTheBall() )
   {
      pGoalKeeper->getSteeringBehavior()->pursuitOff();
      SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
      pGoalKeeper->getStateMachine()->changeState( GoalKick::getInstance() );
      SoccerGame::getGameInstance()->setGameOn( false );
   }
}

void InterceptBall::exit( GoalKeeper* pGoalKeeper )
{
}

InterceptBall* InterceptBall::getInstance()
{
   static InterceptBall interceptBallState;
   return &interceptBallState;
}
