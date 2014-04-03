// This class contains all the state classes for field players.
// Each class has an enter, execute and an exit function. Execute function of the state class the plaeyr currently
// is in gets called  in every update. Entry and Exit only get called when the state changes
// getName is used for debug purposes only. 
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

//*****************************************************************

class FieldPlayerReturnHome :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   const char* getStateName() const { return "FieldPlayerReturnHome"; }

   static FieldPlayerReturnHome* getInstance();

private:
   FieldPlayerReturnHome(void){};
};
