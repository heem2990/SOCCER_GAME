#pragma once
#include "Players.h"

class Teams;

class GoalKeeper :
   public Players
{
public:
   GoalKeeper(  Teams* pMyTeam  );
   ~GoalKeeper(void);
};

