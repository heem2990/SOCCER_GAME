#include "GoalKeeperStates.h"

// ReturnHome State functions
void ReturnHome::enter( GoalKeeper* pGoalKeeper )
{
}

void ReturnHome::execute( GoalKeeper* pGoalKeeper )
{
}

void ReturnHome::exit( GoalKeeper* pGoalKeeper )
{
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
}

void TendGoal::execute( GoalKeeper* pGoalKeeper )
{
}

void TendGoal::exit( GoalKeeper* pGoalKeeper )
{
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
}

void GoalKick::execute( GoalKeeper* pGoalKeeper )
{
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
}

void InterceptBall::execute( GoalKeeper* pGoalKeeper )
{
}

void InterceptBall::exit( GoalKeeper* pGoalKeeper )
{
}

InterceptBall* InterceptBall::getInstance()
{
   static InterceptBall interceptBallState;
   return &interceptBallState;
}
