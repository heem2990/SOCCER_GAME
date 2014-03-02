#pragma once
#include "Players.h"

class GoalKeeper :
   public Players
{
public:
   GoalKeeper( TEAM::id myTeam );
   ~GoalKeeper(void);
};

