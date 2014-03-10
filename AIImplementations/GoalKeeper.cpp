#include "GoalKeeper.h"
#include "Teams.h"
#include "Message.h"
#include "GoalKeeperStates.h"
#include "GoalPosts.h"
#include <math.h>
#include "SoccerBall.h"

GoalKeeper::GoalKeeper( Teams* pMyTeam )
   : Players( pMyTeam, PlayerPositions::GOALKEEPER )
   , m_pMyStateMachine()
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
         m_pMyStateMachine->changeState( ReturnHome::getInstance() );
         return true;
         break;
      }
   case MESSAGE_TYPES::RECEIVE_BALL:
      {
         m_pMyStateMachine->changeState( InterceptBall::getInstance() );
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
