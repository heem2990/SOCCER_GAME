#pragma once
#include "Players.h"
#include"StateMachine.h"

class Message;
class Teams;

class FieldPlayers :
   public Players
{
public:
   FieldPlayers( Teams* pMyTeam, PlayerPositions::id myPosition );
   ~FieldPlayers(void);

   bool handleMessage( const Message& msg );
   virtual void update();
   StateMachine< FieldPlayers >* getStateMachine() const { return m_pMyStateMachine; }

private:

   StateMachine< FieldPlayers >* m_pMyStateMachine;  

};

