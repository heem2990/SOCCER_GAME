#pragma once
#include "State.h"

class GoalKeeper;

class ReturnHome :
   public State< GoalKeeper >
{
public:
   void enter( GoalKeeper* );
   void execute( GoalKeeper* );
   void exit( GoalKeeper* );
   const char* getStateName() const { return "ReturnHome"; }
   
   static ReturnHome* getInstance();

private:
   ReturnHome(void){};
};

//*****************************************************************

class TendGoal :
   public State< GoalKeeper >
{
public:
   void enter( GoalKeeper* );
   void execute( GoalKeeper* );
   void exit( GoalKeeper* );
   const char* getStateName() const { return "TendGoal"; }
   
   static TendGoal* getInstance();

private:
   TendGoal(void){};
};

//*****************************************************************

class GoalKick :
   public State< GoalKeeper >
{
public:
   void enter( GoalKeeper* );
   void execute( GoalKeeper* );
   void exit( GoalKeeper* );
   const char* getStateName() const { return "GoalKick"; }
   
   static GoalKick* getInstance();

private:
   GoalKick(void){};
};

//*****************************************************************

class InterceptBall :
   public State< GoalKeeper >
{
public:
   void enter( GoalKeeper* );
   void execute( GoalKeeper* );
   void exit( GoalKeeper* );
   const char* getStateName() const { return "InterceptBall"; }
   
   static InterceptBall* getInstance();

private:
   InterceptBall(void){};
};

//*****************************************************************
