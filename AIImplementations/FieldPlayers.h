// specialized class for all the players except goalkeepers
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
   virtual void draw();
   StateMachine< FieldPlayers >* getStateMachine() const { return m_pMyStateMachine; }

private:
   
   // States handled differently for goalkeepers and field players, thus this object is not in Players class
   StateMachine< FieldPlayers >* m_pMyStateMachine;
   ALLEGRO_FONT* m_playerStateFont;  // used to debug the player state. TODO: Remove after debugging. 

};

