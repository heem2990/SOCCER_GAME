#pragma once
#include<vector>
#include"StateMachine.h"
#include"Players.h"

class FieldPlayers;
class GoalKeeper;

class Teams
{
public:
   Teams( TEAM::id myTeam );
   ~Teams( void );
   void update();
   void draw();

private:
   TEAM::id m_myTeam;
   std::vector< FieldPlayers * > m_playersOnTeam;
   GoalKeeper* m_pGoalkeeper;
   bool m_hasBall;
   
   StateMachine< Teams >* m_pMyStateMachine;
};

