#pragma once
#include "Players.h"

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

private:

};

