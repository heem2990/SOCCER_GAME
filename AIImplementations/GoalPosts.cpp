#include "GoalPosts.h"
#include "MyRect.h"
#include "SoccerBall.h"

GoalPosts::GoalPosts( glm::vec2 topLeft, glm::vec2 botRight, glm::vec2 facing  )
   : MyRect( topLeft, botRight )
   , m_facing( facing ) // Keeps track of which goal post it is.
{
}


GoalPosts::~GoalPosts(void)
{
}

bool GoalPosts::checkGoal()
{
   if( contains( SoccerBall::getSoccerBallInstance()->getPosition() ) )
   {
      return true;
   }
   
   return false;
}