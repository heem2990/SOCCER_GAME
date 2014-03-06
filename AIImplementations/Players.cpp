#include "Players.h"
#include "SoccerGame.h"
#include <iostream>
#include <glm\glm.hpp>
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include "Teams.h"

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
   "redBot.png",
   "greenBot.png"
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
   : MovingEntity( PLAYER_IMAGES[ pMyTeam->getTeamColor() ], SoccerGame::getRegions()[ PLAYER_POSITONS[ pMyTeam->getTeamColor() ][ myPosition ] ]->getCenter(), glm::vec2() ,PLAYER_DIRECTION[ pMyTeam->getTeamColor() ], PLAYERS_MAX_SPEED ) // change this according to playerPosition and team
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) )
   , m_pMyStateMachine()
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
   al_draw_text( m_playerStateFont, al_map_rgb( 255, 255, 255 ), getPosition().x , getPosition().y, 0, "state" );
   MovingEntity::draw();
}

void Players::update()
{
   draw();
   m_pSteeringBehavior->calculateForce();
   MovingEntity::update();
}

bool Players::isPlayerHome()
{
	return false;
	//TODO check if the player is home and return true
}

bool Players::isInKickingRangeOfTheBall() const
{
	if( sqrMag( getPosition() - SoccerBall::getSoccerBallInstance()->getPosition() ) <= 100.0f ) // TODO: 100 is hardcoded, change. 
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
   return false;
   // TODO Check the 
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

void Players::setHomeRegionAsTarget() const
{
   m_pSteeringBehavior->setArriveTarget( SoccerGame::getRegions()[ m_homeRegion ]->getCenter() );
}