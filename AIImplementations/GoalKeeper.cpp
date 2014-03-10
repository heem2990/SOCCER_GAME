#include "GoalKeeper.h"
#include "Teams.h"
#include "Message.h"
#include "GoalKeeperStates.h"
#include "Players.h"
#include "GoalPosts.h"
#include <math.h>
#include "SoccerBall.h"

GoalKeeper::GoalKeeper( Teams* pMyTeam )
   : Players( pMyTeam, PlayerPositions::GOALKEEPER )
{
}


GoalKeeper::~GoalKeeper(void)
{
}


bool GoalKeeper::handleMessage( const Message& msg )
{
   switch ( msg.getMessageType() )
   {
   case MESSAGE_TYPES::GO_HOME:
      {
         getStateMachine()->changeState( ReturnHome::getInstance() );
         return true;
         break;
      }
   case MESSAGE_TYPES::RECEIVE_BALL:
      {
         getStateMachine()->changeState( InterceptBall::getInstance() );
         return true;
         break;
      }
   default:
      {
         return false;
         break;
      }
   }
   return false;
}

float GoalKeeper::getSqrDistanceFromGoal()
{
   glm::vec2 goalPostPosition = getMyTeam()->getGoalPost()->getCenter();
   glm::vec2 vecToGoalKeeper = getPosition() - goalPostPosition;
   float sqrMag = vecToGoalKeeper.x * vecToGoalKeeper.x + vecToGoalKeeper.y * vecToGoalKeeper.y;

   return sqrMag;
}

bool GoalKeeper::isTooFarFromGoal()
{
   if( getSqrDistanceFromGoal() > 22500.0f ) // TODO: Magic number make constant. Says that if distance is more than 150 pixels ( 22500 = 150 * 150 because sqrd distance )
   {
      return true;
   }
   return false;
}

bool GoalKeeper::isBallWithinInterceptRanger()
{
   glm::vec2 vecToBall = getPosition() - SoccerBall::getSoccerBallInstance()->getPosition();
   float sqrDist = vecToBall.x * vecToBall.x + vecToBall.y * vecToBall.y;

   if( sqrDist <= 10000.0f ) // TODO: Magic number. Says that if ball is about 100 pixels away.
   {
      return true;
   }

   return false;
}