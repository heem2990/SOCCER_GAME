#pragma once
#include "State.h"

class FieldPlayers;
class ReturnHome :
   public State< FieldPlayers >
{
public:
   ReturnHome(void);
   ~ReturnHome(void);

   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
};

class Attack :
   public State< FieldPlayers >
{
public:
   Attack(void);
   ~Attack(void);

   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
};

class SupportPlayerWithBall :
   public State< FieldPlayers >
{
public:
   SupportPlayerWithBall(void);
   ~SupportPlayerWithBall(void);

   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
};
