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
   std::cout<<"Goalkeeper going home"<<std::endl;
   pGoalKeeper->setHomeRegionAsTarget();
   pGoalKeeper->getSteeringBehavior()->arriveOn();
}

void ReturnGoalkeeperHome::execute( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->setHomeRegionAsTarget();

   if( pGoalKeeper->isPlayerHome() || !pGoalKeeper->getMyTeam()->hasControl() )
   {
      pGoalKeeper->getStateMachine()->changeState( TendGoal::getInstance() );
   }
}

void ReturnGoalkeeperHome::exit( GoalKeeper* pGoalKeeper )
{
   std::cout<<"Exiting Return Home"<<std::endl;
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
   std::cout<<"GoalKeeper entering TendGoal state"<<std::endl;
   pGoalKeeper->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   glm::vec2 goalCenter = pGoalKeeper->getMyTeam()->getGoalPost()->getCenter() ;
   std::cout<<goalCenter.x<<" "<<goalCenter.y;
   pGoalKeeper->getSteeringBehavior()->setInterPoseStaticTarget( goalCenter, 0.2 );
   pGoalKeeper->getSteeringBehavior()->interposeOn();
   pGoalKeeper->setLookAtTarget( SoccerBall::getSoccerBallInstance() );
}

void TendGoal::execute( GoalKeeper* pGoalKeeper )
{
   if( pGoalKeeper->isInKickingRangeOfTheBall() )
   {
      SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
      pGoalKeeper->setHasBall( true );
      pGoalKeeper->getStateMachine()->changeState( GoalKick::getInstance() );
      return;
   }

   if( pGoalKeeper->isBallWithinInterceptRanger() )
   {
      pGoalKeeper->getStateMachine()->changeState( InterceptBall::getInstance() );
   }

   if( pGoalKeeper->isTooFarFromGoal() && pGoalKeeper->getMyTeam()->hasControl() )
   {
      pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
   }
}

void TendGoal::exit( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->interposeOff();
   pGoalKeeper->lookAtOff();
   std::cout<<"Goalkeeper exiting TendGoal Stae"<<std::endl;
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
   std::cout<<"Entering the goal kick state"<<std::endl;
   pGoalKeeper->getMyTeam()->setPlayerWithBall( pGoalKeeper );
   pGoalKeeper->getMyTeam()->sendFieldPlayersHome();
   pGoalKeeper->getMyTeam()->getOpponent()->sendPlayersHome();
   // TODO: Check if we will need to set velocity of trapped ball equal to goalKeepers 
}

void GoalKick::execute( GoalKeeper* pGoalKeeper )
{
   Players* passReceivingPlayer = NULL;
   glm::vec2 passPosition( 0, 0 );
   if( pGoalKeeper->getMyTeam()->findPass( pGoalKeeper, passReceivingPlayer, passPosition, 30, 10 ) )
   {
      if( passReceivingPlayer )
      {
         SoccerBall::getSoccerBallInstance()->kick( glm::normalize( passPosition - pGoalKeeper->getPosition() ), 60 );
         pGoalKeeper->setHasBall( false );

         MessageDispatcher::getInstance()->dispatchMessage( 0,pGoalKeeper,passReceivingPlayer, MESSAGE_TYPES::RECEIVE_BALL, &passPosition );
         pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
         return;
      }
   }
   //SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
}

void GoalKick::exit( GoalKeeper* pGoalKeeper )
{
   std::cout<<"Exiting the goal kick state"<<std::endl;
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
   std::cout<<"Entering the Intercept ball state"<<std::endl;
   pGoalKeeper->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
   pGoalKeeper->getSteeringBehavior()->pursuitOn();
}

void InterceptBall::execute( GoalKeeper* pGoalKeeper )
{
   if( pGoalKeeper->isTooFarFromGoal() && !pGoalKeeper->isPlayerClosestToBall() )
   {
      pGoalKeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
      return;
   }
   if( pGoalKeeper->isInKickingRangeOfTheBall() )
   {
      SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
      pGoalKeeper->getStateMachine()->changeState( GoalKick::getInstance() );
   }
}

void InterceptBall::exit( GoalKeeper* pGoalKeeper )
{
   std::cout<<"Exiting the Intercept ball state"<<std::endl;
}

InterceptBall* InterceptBall::getInstance()
{
   static InterceptBall interceptBallState;
   return &interceptBallState;
}
