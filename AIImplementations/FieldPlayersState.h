#pragma once
#include "State.h"

class Players;
class Wait :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "Wait"; }
   
   static Wait* getInstance();

private:
   Wait(void){};
};

//*****************************************************************

class ChaseBall :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "ChaseBall"; }

   static ChaseBall* getInstance();

private:
   ChaseBall(void){};
};

//*****************************************************************

class ReceiveBall :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "ReceiveBall"; }

   static ReceiveBall* getInstance();

private:
   ReceiveBall(void){};
};

//*****************************************************************

class Dribble :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "Dribble"; }
   
   static Dribble* getInstance();

private:
   Dribble(void){};
};

//*****************************************************************

class KickBall :
	public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "KickBall"; }

   static KickBall* getInstance();

private:
   KickBall(void){};
};

//*****************************************************************

class SupportPlayerWithBall :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "SupportPlayerWithBall"; }

   static SupportPlayerWithBall* getInstance();

private:
   SupportPlayerWithBall(void){};
};

//*****************************************************************

class ReturnHome :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "ReturnHome"; }

   static ReturnHome* getInstance();

private:
   ReturnHome(void){};
};
