#pragma once
#include "Players.h"

class FieldPlayers :
   public Players
{
public:
   FieldPlayers( TEAM::id myTeam, PlayerPositions::id myPosition );
   ~FieldPlayers(void);

private:

};

