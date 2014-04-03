// Specialized class for goalkeepers, it will handle the messages and state of goalkeepers. 
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
   bool handleMessage( const Message& msg );
   StateMachine< GoalKeeper >* getStateMachine() const { return m_pMyStateMachine; }

   virtual void update();
   virtual void draw();

private:

   StateMachine< GoalKeeper >* m_pMyStateMachine;
   ALLEGRO_FONT* m_playerStateFont;    

};

