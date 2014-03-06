#pragma once
#include "Players.h"

class Teams;

class FieldPlayers :
   public Players
{
public:
   FieldPlayers( Teams* pMyTeam, PlayerPositions::id myPosition );
   ~FieldPlayers(void);

private:

};

