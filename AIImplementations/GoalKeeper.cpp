#include "GoalKeeper.h"

GoalKeeper::GoalKeeper( TEAM::id myTeam )
   : Players( myTeam, PlayerPositions::GOALKEEPER )
{
}


GoalKeeper::~GoalKeeper(void)
{
}
