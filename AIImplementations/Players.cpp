#include "Players.h"
#include "SoccerGame.h"
#include <iostream>
#include <glm\glm.hpp>
#include "SteeringBehaviors.h"
#include "SoccerBall.h"

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

Players::Players( TEAM::id myTeam, PlayerPositions::id myPosition )
   : MovingEntity( PLAYER_IMAGES[ myTeam ], SoccerGame::getRegions()[ PLAYER_POSITONS[ myTeam ][ myPosition ] ]->getCenter(), glm::vec2() ,PLAYER_DIRECTION[ myTeam ], PLAYERS_MAX_SPEED ) // change this according to playerPosition and team
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) )
   , m_myTeam( myTeam )
   , m_pMyStateMachine()
   , m_pSteeringBehavior( NULL )
   , m_bHasBall( false )
   , m_isClosestPlayerToBall( false )
   , m_homeRegion( PLAYER_POSITONS[ myTeam ][ myPosition ] )
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

bool Players::isInKickingRangeOfTheBall()
{
	glm::vec2 vectorToBall = getPosition() - SoccerBall::getSoccerBallInstance()->getPosition();
	float sqrDistance = ( vectorToBall.x * vectorToBall.x ) + ( vectorToBall.y * vectorToBall.y );
	if( sqrDistance <= 100.0f )
	{
		return true;
	}
	else
	{
		return false;
	}
}