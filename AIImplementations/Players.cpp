#include "Players.h"
#include"SoccerGame.h"
#include<iostream>
#include<glm\glm.hpp>

const int NUM_PLAYERS = 5;

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
   : MovingEntity( PLAYER_IMAGES[ myTeam ], SoccerGame::getRegions()[ PLAYER_POSITONS[ myTeam ][ myPosition ] ]->getCenter(), glm::vec2() ,PLAYER_DIRECTION[ myTeam ] ) // change this according to playerPosition and team
   , m_myStateMachine()
   , m_playerStateFont( al_load_font( "arial.ttf" , 24, 0 ) )
   , m_homeRegion( PLAYER_POSITONS[ myTeam ][ myPosition ] )
{
}


Players::~Players(void)
{
   al_destroy_font( m_playerStateFont );
}

void Players::draw()
{
   al_draw_text( m_playerStateFont, al_map_rgb( 255, 255, 255 ), getPosition().x , getPosition().y, 0, "state" );
   MovingEntity::draw();
}

void Players::update()
{
   steeringBehavior();
   draw();
   MovingEntity::update();
}

void Players::steeringBehavior()
{
   glm::vec2 target = getTarget();
   glm::vec2 directionToGoto = glm::normalize( target - getPosition() );
   setVelocity( 3.0f * directionToGoto );   
}