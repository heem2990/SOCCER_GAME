//A class to help keep track of the posts on the field.
#pragma once
#include "MyRect.h"

class GoalPosts :
   public MyRect
{
public:
   GoalPosts( glm::vec2 topLeft, glm::vec2 botRight, glm::vec2 facing );
   ~GoalPosts(void);

   bool checkGoal();
   glm::vec2 getFacing() const { return m_facing; }

private:
   glm::vec2 m_facing;

};

