#include "GoalKeeper.h"
#include "Teams.h"

GoalKeeper::GoalKeeper( Teams* pMyTeam )
   : Players( pMyTeam, PlayerPositions::GOALKEEPER )
{
}


GoalKeeper::~GoalKeeper(void)
{
}
