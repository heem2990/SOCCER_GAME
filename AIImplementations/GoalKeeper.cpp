#include "GoalKeeper.h"
#include "Teams.h"
#include "Message.h"
#include "GoalKeeperStates.h"
#include "GoalPosts.h"
#include <math.h>
#include "SoccerBall.h"

static const int MAX_DISTANCE_FROM_GOAL = 40000.0f; // This is squared distance, so its 100 pixels. 

GoalKeeper::GoalKeeper( Teams* pMyTeam )
   : Players( pMyTeam, PlayerPositions::GOALKEEPER )
   , m_pMyStateMachine( new StateMachine< GoalKeeper >( this ) )
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) ) 
{
   m_pMyStateMachine->setPreviousState( ReturnGoalkeeperHome::getInstance() );
   m_pMyStateMachine->setCurrentState( ReturnGoalkeeperHome::getInstance() );
}


GoalKeeper::~GoalKeeper(void)
{
   delete m_pMyStateMachine;
}


bool GoalKeeper::handleMessage( const Message& msg )
{
   switch ( msg.getMessageType() )
   {
   case MESSAGE_TYPES::GO_HOME:
      {
         m_pMyStateMachine->changeState( ReturnGoalkeeperHome::getInstance() );
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
   if( getSqrDistanceFromGoal() > MAX_DISTANCE_FROM_GOAL ) // TODO: Magic number make constant. Says that if distance is more than 150 pixels ( 22500 = 150 * 150 because sqrd distance )
   {
      return true;
   }
   return false;
}

void GoalKeeper::update()
{
	Players::update();
	m_pMyStateMachine->update();
}

void GoalKeeper::draw()
{   
   Players::draw();
   al_draw_text( m_playerStateFont, al_map_rgb( 255, 255, 255 ), getPosition().x , getPosition().y, 0, m_pMyStateMachine->getCurrentState()->getStateName() );
}

bool GoalKeeper::canGoalKeeperGetBall()
{
   glm::vec2 fromPostToBall = getMyTeam()->getGoalPost()->getCenter() - SoccerBall::getSoccerBallInstance()->getPosition();
   if( fromPostToBall.x * fromPostToBall.x + fromPostToBall.y * fromPostToBall.y <= 10000.0f ) // TODO: 100 is hardcoded, change. 
	{
		return true;
	}
	else
	{
		return false;
	}
}