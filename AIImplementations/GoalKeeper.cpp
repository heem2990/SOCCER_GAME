#include "GoalKeeper.h"
#include "Teams.h"
#include "Message.h"
#include "GoalKeeperStates.h"

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