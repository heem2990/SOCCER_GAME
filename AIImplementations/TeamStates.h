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