#include "FieldPlayers.h"
#include "Message.h"
#include "StateMachine.h"
#include "FieldPlayersState.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "MessageDispatcher.h"

static const int MAX_PASSING_FORCE = 10.0f; // check values.

FieldPlayers::FieldPlayers( Teams* pMyTeam, PlayerPositions::id myPosition )
   : Players( pMyTeam, myPosition )
{
}

FieldPlayers::~FieldPlayers(void)
{
}

bool FieldPlayers::handleMessage( const Message& msg )
{
   switch ( msg.getMessageType() )
   {
   case MESSAGE_TYPES::GO_HOME:
      {
         getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );

         return true;
         break;
      }
   case MESSAGE_TYPES::PASS_TO_ME:
      {
         glm::vec2 receivingPlayerPos = msg.getSender()->getPosition();

         if( isPlayerWithinReceivingRange() )
         {
            return true;
         }
         
         SoccerBall::getSoccerBallInstance()->kick( receivingPlayerPos - SoccerBall::getSoccerBallInstance()->getPosition(), MAX_PASSING_FORCE );
         MessageDispatcher::getInstance()->dispatchMessage( 0.0f, this, msg.getSender(), MESSAGE_TYPES::RECEIVE_BALL, NULL );
         getStateMachine()->changeState( Wait::getInstance() );
         // TODO: find support?

         return true;
         break;
      }
   case MESSAGE_TYPES::RECEIVE_BALL:
      {
         getSteeringBehavior()->setArriveTarget( *( static_cast< glm::vec2* >( msg.getExtraInfo() ) ) );
         getStateMachine()->changeState( ReceiveBall::getInstance() );
         return true;
         break;
      }
   case MESSAGE_TYPES::SUPPORT_ATTACKER:
      {
         if( getStateMachine()->getCurrentState() == SupportPlayerWithBall::getInstance() )
         {
            return true;
         }

         getSteeringBehavior()->setArriveTarget( glm::vec2() /*TODO HEEM Get support spot here*/ ); 
         getStateMachine()->changeState( SupportPlayerWithBall::getInstance() );

         return true;
         break;
      }
   case MESSAGE_TYPES::WAIT:
      {
         getStateMachine()->changeState( Wait::getInstance() );
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

void FieldPlayers::update()
{
   if( isPlayerControllingTheBall() )
   {
      setMaxSpeed( 2.0f ); // TODO CHANGE magic number;
   }
   else
   {
      setMaxSpeed( 5.0f ); // TODO change magic number
   }
   Players::update();
}