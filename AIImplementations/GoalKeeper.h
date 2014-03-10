#pragma once
#include "Players.h"

class Teams;

class GoalKeeper :
   public Players
{
public:
   GoalKeeper(  Teams* pMyTeam  );
   ~GoalKeeper(void);

   float getSqrDistanceFromGoal();

   bool isTooFarFromGoal();
   bool isBallWithinInterceptRanger();
   bool handleMessage( const Message& msg );
};

