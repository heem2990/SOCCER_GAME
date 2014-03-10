#pragma once
#include "Players.h"
#include"StateMachine.h"

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
   StateMachine< GoalKeeper >* getStateMachine() const { return m_pMyStateMachine; }

private:

   StateMachine< GoalKeeper >* m_pMyStateMachine;  

};

