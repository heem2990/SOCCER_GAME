// State classes for the teams. 
// Each class has an enter, execute and an exit function. Execute function of the state class the goalkeeper currently
// is in gets called  in every update. Entry and Exit only get called when the state changes
// getName is used for debug purposes only. 
#pragma once
#include "State.h"

class Teams;

class Attacking :
   public State< Teams >
{
public:
   void enter( Teams* );
   void execute( Teams* );
   void exit( Teams* );
   const char* getStateName() const { return "Attacking"; }
   
   static Attacking* getInstance();

private:
   Attacking(void){};
};

//*****************************************************************

class Defending :
   public State< Teams >
{
public:
   void enter( Teams* );
   void execute( Teams* );
   void exit( Teams* );
   const char* getStateName() const { return "Defending"; }

   static Defending* getInstance();

private:
   Defending(void){};
};

//*****************************************************************

class KickOff :
   public State< Teams >
{
public:
   void enter( Teams* );
   void execute( Teams* );
   void exit( Teams* );
   const char* getStateName() const { return "KickOff"; }

   static KickOff* getInstance();

private:
   KickOff(void){};
};