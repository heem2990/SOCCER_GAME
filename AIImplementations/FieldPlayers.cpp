#include "FieldPlayers.h"
#include "Message.h"
#include "StateMachine.h"
#include "FieldPlayersState.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "MessageDispatcher.h"
#include "Teams.h"
#include "SupportSpotCalculator.h"

static const int MAX_PASSING_FORCE = 40.0f; // check values.
static const int NORMAL_SPEED = 5.0f;
static const int SPEED_WITH_BALL = 2.0f;

FieldPlayers::FieldPlayers( Teams* pMyTeam, PlayerPositions::id myPosition )
   : Players( pMyTeam, myPosition )
   , m_pMyStateMachine( new StateMachine< FieldPlayers >( this ) )
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) )
{
   m_pMyStateMachine->setPreviousState( FieldPlayerReturnHome::getInstance() );
   m_pMyStateMachine->setCurrentState( FieldPlayerReturnHome::getInstance() );
}

FieldPlayers::~FieldPlayers(void)
{
   al_destroy_font( m_playerStateFont );
   delete m_pMyStateMachine;
}

bool FieldPlayers::handleMessage( const Message& msg )
{
   switch ( msg.getMessageType() )
   {
   case MESSAGE_TYPES::GO_HOME:
      {
         m_pMyStateMachine->changeState( FieldPlayerReturnHome::getInstance() );

         return true;
         break;
      }
   case MESSAGE_TYPES::PASS_TO_ME:
      {
         glm::vec2 receivingPlayerPos = msg.getSender()->getPosition();

         if( !isInKickingRangeOfTheBall() )
         {
            return true;
         }
         
         SoccerBall::getSoccerBallInstance()->kick( receivingPlayerPos - SoccerBall::getSoccerBallInstance()->getPosition(), MAX_PASSING_FORCE );
         MessageDispatcher::getInstance()->dispatchMessage( 0.0f, this, msg.getSender(), MESSAGE_TYPES::RECEIVE_BALL, &receivingPlayerPos );
         m_pMyStateMachine->changeState( Wait::getInstance() );
         setHasBall( false );

         findSupportingPlayer();

         return true;
         break;
      }
   case MESSAGE_TYPES::RECEIVE_BALL:
      {
         getSteeringBehavior()->setArriveTarget( *( static_cast< glm::vec2* >( msg.getExtraInfo() ) ) );
         m_pMyStateMachine->changeState( ReceiveBall::getInstance() );
         return true;
         break;
      }
   case MESSAGE_TYPES::SUPPORT_ATTACKER:
      {
         if( m_pMyStateMachine->getCurrentState() == SupportPlayerWithBall::getInstance() )
         {
            return true;
         }

         getSteeringBehavior()->setArriveTarget( getMyTeam()->getSupportSpot()->getBestSupportSpot() ); 
         m_pMyStateMachine->changeState( SupportPlayerWithBall::getInstance() );
         return true;
         break;
      }
   case MESSAGE_TYPES::WAIT:
      {
         m_pMyStateMachine->changeState( Wait::getInstance() );
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
   Players::update();
	m_pMyStateMachine->update();
   if( isPlayerControllingTheBall() )
   {
      setMaxSpeed( SPEED_WITH_BALL ); // TODO CHANGE magic number; The speed is reduced if the player is dribbling the ball. 
   }
   else
   {
      setMaxSpeed( NORMAL_SPEED ); // TODO change magic number--- Speed set to normal
   }
}

void FieldPlayers::draw()
{
   Players::draw();
   al_draw_text( m_playerStateFont, al_map_rgb( 255, 255, 255 ), getPosition().x , getPosition().y, 0, m_pMyStateMachine->getCurrentState()->getStateName() ); // TODO:Remove , debug text for state names.
}