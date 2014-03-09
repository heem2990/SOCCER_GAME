#include "GoalKeeperStates.h"
#include "Players.h"

// ReturnHome State functions
void ReturnHome::enter( Players* pGoalKeeper )
{
}

void ReturnHome::execute( Players* pGoalKeeper )
{
}

void ReturnHome::exit( Players* pGoalKeeper )
{
}

ReturnHome* ReturnHome::getInstance()
{
   static ReturnHome returnHomeState;
   return &returnHomeState;
}
 
//*****************************************************************
// TendGoal State functions

void TendGoal::enter( Players* pGoalKeeper )
{
}

void TendGoal::execute( Players* pGoalKeeper )
{
}

void TendGoal::exit( Players* pGoalKeeper )
{
}

TendGoal* TendGoal::getInstance()
{
   static TendGoal tendGoalState;
   return &tendGoalState;
}

//*****************************************************************
// goalKick State functions

void GoalKick::enter( Players* pGoalKeeper )
{
}

void GoalKick::execute( Players* pGoalKeeper )
{
}

void GoalKick::exit( Players* pGoalKeeper )
{
}

GoalKick* GoalKick::getInstance()
{
   static GoalKick goalKickState;
   return &goalKickState;
}

//*****************************************************************
// InterceptBall State functions

void InterceptBall::enter( Players* pGoalKeeper )
{
}

void InterceptBall::execute( Players* pGoalKeeper )
{
}

void InterceptBall::exit( Players* pGoalKeeper )
{
}

InterceptBall* InterceptBall::getInstance()
{
   static InterceptBall interceptBallState;
   return &interceptBallState;
}
