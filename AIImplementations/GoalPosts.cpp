#include "GoalPosts.h"
#include "MyRect.h"
#include "SoccerBall.h"

GoalPosts::GoalPosts( glm::vec2 topLeft, glm::vec2 botRight )
   : MyRect( topLeft, botRight )
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