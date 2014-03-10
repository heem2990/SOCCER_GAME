#include "GoalKeeperStates.h"
#include "GoalKeeper.h"
#include <iostream>
#include "SteeringBehaviors.h"
#include "Teams.h"
#include "SoccerBall.h"
#include "SoccerGame.h"

// ReturnHome State functions
void ReturnHome::enter( GoalKeeper* pGoalKeeper )
{
   std::cout<<"Goalkeeper going home"<<std::endl;
   pGoalKeeper->getSteeringBehavior()->arriveOn();
}

void ReturnHome::execute( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->setHomeRegionAsTarget();

   if( pGoalKeeper->isPlayerHome() || pGoalKeeper->getMyTeam()->hasControl() )
   {
      pGoalKeeper->getStateMachine()->changeState( TendGoal::getInstance() );
   }
}

void ReturnHome::exit( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->arriveOff();
}

ReturnHome* ReturnHome::getInstance()
{
   static ReturnHome returnHomeState;
   return &returnHomeState;
}
 
//*****************************************************************
// TendGoal State functions

void TendGoal::enter( GoalKeeper* pGoalKeeper )
{
   std::cout<<"GoalKeeper entering TendGoal state"<<std::endl;
   pGoalKeeper->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() ); // TODO: Change this to proper target.
   pGoalKeeper->getSteeringBehavior()->interposeOn();
}

void TendGoal::execute( GoalKeeper* pGoalKeeper )
{
   // TODO: set target as interpose target.
   if( pGoalKeeper->isInKickingRangeOfTheBall() )
   {
      SoccerBall::getSoccerBallInstance()->trap( pGoalKeeper );
      pGoalKeeper->getStateMachine()->changeState( GoalKick::getInstance() );
      return;
   }
   // TODO: if ball is within intercept range, intercept. 
}

void TendGoal::exit( GoalKeeper* pGoalKeeper )
{
   pGoalKeeper->getSteeringBehavior()->interposeOff();
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
   pGoalKeeper->getMyTeam()->sendPlayersHome();
   pGoalKeeper->getMyTeam()->getOpponent()->sendPlayersHome();
}

void GoalKick::execute( GoalKeeper* pGoalKeeper )
{
   //TODO: find pass, if found send message to the receiver else just attach ball to keeper;
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
   pGoalKeeper->getSteeringBehavior()->pursuitOn();
}

void InterceptBall::execute( GoalKeeper* pGoalKeeper )
{
   //TODO: If keeper is too far from goal, and if keeper is not the closest player on pitch to ball change state to return home
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
