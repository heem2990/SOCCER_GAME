#pragma once
#include "State.h"
#include "Players.h"

class Attack :
   public State< Players >
{
public:
   Attack(void);
   ~Attack(void);

   void enter( Players* pPlayer );
   void execute( Players* pPlayer );
   void exit( Players* player );

};

