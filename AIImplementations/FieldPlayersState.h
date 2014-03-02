#pragma once
#include "State.h"

class FieldPlayers;

class Wait :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "Wait"; }
   
   static Wait* getInstance();

private:
   Wait(void){};
};

//*****************************************************************

class ChaseBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "ChaseBall"; }

   static ChaseBall* getInstance();

private:
   ChaseBall(void){};
};

//*****************************************************************

class ReceiveBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "ReceiveBall"; }

   static ReceiveBall* getInstance();

private:
   ReceiveBall(void){};
};

//*****************************************************************

class Dribble :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "Dribble"; }
   
   static Dribble* getInstance();

private:
   Dribble(void){};
};

//*****************************************************************

class KickBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "KickBall"; }

   static KickBall* getInstance();

private:
   KickBall(void){};
};

//*****************************************************************

class SupportPlayerWithBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "SupportPlayerWithBall"; }

   static SupportPlayerWithBall* getInstance();

private:
   SupportPlayerWithBall(void){};
};
