// State classes for goalkeepers.
// Each class has an enter, execute and an exit function. Execute function of the state class the goalkeeper currently
// is in gets called  in every update. Entry and Exit only get called when the state changes
// getName is used for debug purposes only. 
#pragma once
#include "State.h"

class GoalKeeper;

class ReturnGoalkeeperHome :
   public State< GoalKeeper >
{
public:
   void enter( GoalKeeper* );
   void execute( GoalKeeper* );
   void exit( GoalKeeper* );
   const char* getStateName() const { return "ReturnGoalkeeperHome"; }
   
   static ReturnGoalkeeperHome* getInstance();

private:
   ReturnGoalkeeperHome(void){};
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
