#pragma once
#include "MyRect.h"

class GoalPosts :
   public MyRect
{
public:
   GoalPosts( glm::vec2 topLeft, glm::vec2 botRight );
   ~GoalPosts(void);

   bool checkGoal();

private:

};

