#pragma once
#include "State.h"

class Players;

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

//*****************************************************************

class TendGoal :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "TendGoal"; }
   
   static TendGoal* getInstance();

private:
   TendGoal(void){};
};

//*****************************************************************

class GoalKick :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "GoalKick"; }
   
   static GoalKick* getInstance();

private:
   GoalKick(void){};
};

//*****************************************************************

class InterceptBall :
   public State< Players >
{
public:
   void enter( Players* );
   void execute( Players* );
   void exit( Players* );
   const char* getStateName() const { return "InterceptBall"; }
   
   static InterceptBall* getInstance();

private:
   InterceptBall(void){};
};

//*****************************************************************
