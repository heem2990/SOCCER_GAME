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
   static Wait* getInstance();

private:
   Wait(void){};
};

class ChaseBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   static ChaseBall* getInstance();

private:
   ChaseBall(void){};
};

class ReceiveBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   static ReceiveBall* getInstance();

private:
   ReceiveBall(void){};
};

class Dribble :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   static Dribble* getInstance();

private:
   Dribble(void){};
};

class KickBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   static KickBall* getInstance();

private:
   KickBall(void){};
};

class SupportPlayerWithBall :
   public State< FieldPlayers >
{
public:
   void enter( FieldPlayers* );
   void execute( FieldPlayers* );
   void exit( FieldPlayers* );
   static SupportPlayerWithBall* getInstance();

private:
   SupportPlayerWithBall(void){};
};
