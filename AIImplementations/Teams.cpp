#include "Teams.h"
#include "GoalKeeper.h"
#include "Players.h"
#include "FieldPlayers.h"
#include "StateMachine.h"
#include "TeamStates.h"
#include <iostream>
#include "Teams.h"
#include "SteeringBehaviors.h"
#include "GoalPosts.h"
#include "FieldPlayersState.h"
#include "GoalKeeperStates.h"
#include "MessageDispatcher.h"
#include "SupportSpotCalculator.h"
#include "SoccerBall.h"
#include <stdlib.h>

static const char* TEAMS_NAME[2] = 
{
	"Blue",
	"Red"
};
static const int TOTAL_PLAYERS = 4;

glm::vec2 toLocalPos( glm::vec2 position, glm::vec2 axis, glm::vec2 vectorToConvert )
{
   glm::vec2 toPosition = vectorToConvert - position;
   glm::vec2 normalizedAxis = glm::normalize( axis );

   float sinX = normalizedAxis.y;
   float cosX = normalizedAxis.x;

   glm::vec2 localPosition( toPosition.x * cosX - toPosition.y * sinX , toPosition.x * sinX + toPosition.y * cosX );
   return localPosition;
}

Teams::Teams( TEAM::id myTeam, GoalPosts* pMyGoalPost )
   : m_myTeam( myTeam )
   , m_playersOnTeam()
   , m_pGoalkeeper( new GoalKeeper( this ) )
   , m_pPlayerWithBall( NULL )
   , m_pSupportingPlayer( NULL )
   , m_pPlayerClosestToBall( NULL )
   , m_pPlayerReceivingPass( NULL )
   , m_pOpponent( NULL )
   , m_pMyGoalPost( pMyGoalPost )
   , m_pSupportSpotCalculator( new SupportSpotCalculator( this ) )
   , m_hasBall( false )   
   , m_pMyStateMachine( new StateMachine< Teams >( this ) )
{
   for( int i = 0 ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam.push_back( new FieldPlayers( this, ( PlayerPositions::id )( i+1 ) ) ); 
   }
   m_pMyStateMachine->setPreviousState( Defending::getInstance() );
   m_pMyStateMachine->setCurrentState( Defending::getInstance() );
   m_pMyStateMachine->changeState( Defending::getInstance() );
}


Teams::~Teams(void)
{
	for( std::vector< FieldPlayers* >::iterator iter = m_playersOnTeam.begin(); iter != m_playersOnTeam.end() ; ++iter  )
	{
		delete *iter;		
	}
	m_playersOnTeam.clear();

	delete  m_pMyStateMachine;
}

void Teams::update()
{
   m_pMyStateMachine->update();
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->update();
   }
   m_pGoalkeeper->update();
}

void Teams::draw()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->draw();
   }
   m_pGoalkeeper->draw();
   m_pSupportSpotCalculator->debugDraw();
}

const char* Teams::getTeamName()
{
	return TEAMS_NAME[ m_myTeam ];
}

void Teams::sendPlayersHome()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
   }
   m_pGoalkeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
}

void Teams::changeState( State< Teams >* pToState ) const
{
   m_pMyStateMachine->changeState( pToState );
}

bool Teams::arePlayersHome()
{
   MessageDispatcher::getInstance()->dispatchMessage( 0, m_playersOnTeam[ 0 ], m_playersOnTeam[ 1 ], MESSAGE_TYPES::GO_HOME, NULL );
	for( std::vector< FieldPlayers* >::iterator iter = m_playersOnTeam.begin(); iter != m_playersOnTeam.end() ; ++iter )
	{
		if( !(*iter)->isPlayerHome() )
		{
			return false; // returns false is even one of the field player is not home
		}
	}
	if( m_pGoalkeeper->isPlayerHome() )
	{
		return true; // returns true if all fieldPlayers are home and goalKepeer is home.
	}
	return false; // returns false if goalkeeper is not home but the other players are. 
}

bool Teams::doesGoalKeeperHaveBall() const 
{
   return m_pGoalkeeper->isPlayerControllingTheBall();
}

bool Teams::isPassSafeFromOpponent( glm::vec2 from, glm::vec2 to, Players* const receiver, Players* const opponent, float force ) const 
{
   glm::vec2 toTarget = to - from;
   glm::vec2 toOpponent = toOpponent - opponent->getPosition();
	glm::vec2 toTargetNormalized = glm::normalize( to - from );
   glm::vec2 localPositionOfOpponent = toLocalPos( from, toTargetNormalized, opponent->getPosition() );
   
   if( localPositionOfOpponent.x < 0 )
   {
      return true;
   }

   if( ( toTarget.x * toTarget.x + toTarget.y * toTarget.y ) < ( toOpponent.x * toOpponent.x + toOpponent.y * toOpponent.y ) )
   {
      glm::vec2 targetToOpponent = to - opponent->getPosition();
      glm::vec2 receiverToTarget = to - receiver->getPosition();
      if( receiver )
      {
         if( ( targetToOpponent.x * targetToOpponent.x + targetToOpponent.y * targetToOpponent.y ) > ( receiverToTarget.x * receiverToTarget.x + receiverToTarget.y * receiverToTarget.y ) )
         {
            return true;
         }
      }
      else
      {
         return true;
      }
   }

   float timeForBall = SoccerBall::getSoccerBallInstance()->timeToCoverDistance( glm::vec2( 0.0f, 0.0f ), glm::vec2( localPositionOfOpponent.x, 0.0f ), force );

   float OpponentsReach = opponent->getMaxSpeed() * timeForBall;

   if( fabs( localPositionOfOpponent.y ) < OpponentsReach )
   {
      return false;
   }

	return true;
	// get local position of opponent. 
}

bool Teams::isPassSafeFromAllOpponent( glm::vec2 from, glm::vec2 to, Players* const receiver, float force ) const 
{
   for( int i = 0 ; i < 4 ; ++i )
   {
      if( !isPassSafeFromOpponent( from, to, receiver, getOpponent()->getPlayersOnTeam()[ i ], force ) )
      {
         return false;
      }
   }
   return true;
}

glm::vec2 Teams::findGoalShot( float force ) const
{
	int numAttempts = 5;
	glm::vec2 opponentGoalCenter = getOpponent()->getGoalPost()->getCenter();
	
   int minY = getOpponent()->getGoalPost()->gettopLeft().y;
	int maxY = getOpponent()->getGoalPost()->getbotRight().y;
	
   glm::vec2 shotTarget( opponentGoalCenter.x, minY  );

	while( --numAttempts )
	{
      int yDisplacement = rand() % ( maxY - minY ) + minY;
      shotTarget.y = yDisplacement;
      float time = SoccerBall::getSoccerBallInstance()->timeToCoverDistance( SoccerBall::getSoccerBallInstance()->getPosition(), shotTarget, force );
      if( time > 0.0f )
      {
         if( isPassSafeFromAllOpponent( SoccerBall::getSoccerBallInstance()->getPosition(), shotTarget, NULL, force ) )
         {
            return shotTarget;
         }
      }
		// set Random float as the y. 
	}
	return glm::vec2();
}