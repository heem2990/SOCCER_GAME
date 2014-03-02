#pragma once
#include "BaseGameEntity.h"

class GoalPosts :
   public BaseGameEntity
{
public:
   GoalPosts(void);
   ~GoalPosts(void);

   void update();
   void draw();
   void checkGoal();

private:

};

