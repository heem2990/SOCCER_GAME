#include "Players.h"
#include "SoccerGame.h"
#include <iostream>
#include <glm\glm.hpp>
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "Teams.h"
#include "MessageDispatcher.h"
#include "SupportSpotCalculator.h"

const int NUM_PLAYERS = 5;
static const int PLAYERS_MAX_SPEED = 5;
// Initial starting region of the players. 
const int PLAYER_POSITONS[ TEAM::NUM_TEAMS ][ NUM_PLAYERS ] =
{
   {
      16,
      14,
      12,
      11,
      9
   },
   {
      1,
      5,
      3,
      8,
      6
   }
};

char* PLAYER_IMAGES[ TEAM::NUM_TEAMS ] = 
{
   "greenBot.png",
   "redBot.png"
};

const glm::vec2 PLAYER_DIRECTION[ TEAM::NUM_TEAMS ] =
{
   glm::vec2( 1, 0 ),
   glm::vec2( -1, 0 )
};

float sqrMag( glm::vec2 vectorToProcess ) 
{
   return ( vectorToProcess.x * vectorToProcess.x + vectorToProcess.y * vectorToProcess.y );  
}

Players::Players( Teams* pMyTeam, PlayerPositions::id myPosition )
   : MovingEntity( PLAYER_IMAGES[ pMyTeam->getTeamColor() ], glm::vec2( 0, 0 )/*SoccerGame::getRegions()[ PLAYER_POSITONS[ pMyTeam->getTeamColor() ][ myPosition ] ]->getCenter()*/, glm::vec2() ,PLAYER_DIRECTION[ pMyTeam->getTeamColor() ], PLAYERS_MAX_SPEED ) // change this according to playerPosition and team
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) )
   , m_pSteeringBehavior( NULL )
   , m_pMyTeam( pMyTeam )
   , m_myTeamColor( pMyTeam->getTeamColor() )
   , m_bHasBall( false )
   , m_isClosestPlayerToBall( false )
   , m_homeRegion( PLAYER_POSITONS[ pMyTeam->getTeamColor() ][ myPosition ] )
{
   m_pSteeringBehavior = new SteeringBehaviors( this );
}


Players::~Players(void)
{
   al_destroy_font( m_playerStateFont );
   delete m_pSteeringBehavior;
}

void Players::draw()
{
   MovingEntity::draw();
   al_draw_text( m_playerStateFont, al_map_rgb( 255, 255, 255 ), getPosition().x , getPosition().y, 0, "state" );
}

void Players::update()
{
   m_pSteeringBehavior->calculateForce();
   MovingEntity::update();
}

bool Players::isPlayerHome()
{
   if( sqrMag( getPosition() - SoccerGame::getRegions()[ m_homeRegion ]->getCenter() ) <= 100.0f ) // TODO: 100 is hardcoded, change. 
	{
		return true;
	}
	else
	{
		return false;
	}
	//TODO check if the player is home and return true
}

bool Players::isInKickingRangeOfTheBall() const
{
	if( sqrMag( getPosition() - SoccerBall::getSoccerBallInstance()->getPosition() ) <= 1000.0f ) // TODO: 100 is hardcoded, change. 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Players::isAtTarget() const
{
   if( sqrMag( getPosition() - m_pSteeringBehavior->getTarget()->getPosition() ) <= 10.0f ) // 10 so that it might be at max about 3 pixels away/ 
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Players::isAtArriveTarget() const
{
   if( sqrMag( getPosition() - m_pSteeringBehavior->getArriveTarget() ) <= 10.0f ) // 10 so that it might be at max about 3 pixels away/ 
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Players::isPlayerAheadOfAttacker() const
{
   if( m_pMyTeam->hasControl() && m_pMyTeam->getPlayerWithBall() )
   {
      glm::vec2 attackerPosition = m_pMyTeam->getPlayerWithBall()->getPosition();
      if( getPosition().x > attackerPosition.x )
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   return false;
}

bool Players::isPlayerWithinReceivingRange() const 
{
   if( sqrMag( getPosition() - SoccerBall::getSoccerBallInstance()->getPosition() ) <= ( 50 * 50.f) ) // if the ball is less 50 pixels away. 
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool Players::isBallWithinInterceptRanger()
{
   glm::vec2 vecToBall = getPosition() - SoccerBall::getSoccerBallInstance()->getPosition();
   float sqrDist = vecToBall.x * vecToBall.x + vecToBall.y * vecToBall.y;

   if( sqrDist <= 10000.0f ) // TODO: Magic number. Says that if ball is about 100 pixels away.
   {
      return true;
   }
   return false;
}

void Players::setHomeRegionAsTarget() const
{
   m_pSteeringBehavior->setArriveTarget( SoccerGame::getRegions()[ m_homeRegion ]->getCenter() );
}

bool Players::handleMessage( const Message& msg )
{
   return true;
}

void Players::findSupportingPlayer()
{
   if( m_pMyTeam->getSupportingPlayer() == NULL )
   {
      Players* bestSupporter = m_pMyTeam->determineBestSupportingPlayer();
      m_pMyTeam->setSupportingPlayer( bestSupporter );
      MessageDispatcher::getInstance()->dispatchMessage( 0,this, bestSupporter, MESSAGE_TYPES::RECEIVE_BALL, &( m_pMyTeam->getSupportSpot()->getBestSupportSpot() ) );
   }

   Players* bestSupporter = m_pMyTeam->determineBestSupportingPlayer();
   if( bestSupporter && ( bestSupporter != m_pMyTeam->getSupportingPlayer() ) )
   {
      if( m_pMyTeam->getSupportingPlayer() )
      {
         MessageDispatcher::getInstance()->dispatchMessage( 0.0f, this, m_pMyTeam->getSupportingPlayer(), MESSAGE_TYPES::GO_HOME, NULL );
      }

      m_pMyTeam->setSupportingPlayer( bestSupporter );
      MessageDispatcher::getInstance()->dispatchMessage( 0.0f, this, bestSupporter, MESSAGE_TYPES::SUPPORT_ATTACKER, NULL );

   }
}

void Players::setHasBall( bool hasBall )
{
   m_bHasBall = hasBall;
   if( hasBall )
   {
      m_pMyTeam->setPlayerWithBall( this );
      m_pMyTeam->setHasControl( true );
   }
}