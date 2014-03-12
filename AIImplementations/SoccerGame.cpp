#include "SoccerGame.h"
#include <allegro5\allegro.h>
#include "Teams.h"
#include "SoccerBall.h"
#include "GoalPosts.h"
#include "MyRect.h"
#include "Constants.h"
#include <string>
#include <iostream>
#include "Wall.h"

static const int NUM_REGIONS = 18;
static const int WALLS_HEIGHT = 20;
static const int WALLS_WIDTH = 35;
static const int FIELD_HEIGHT = 600; // SCREEN_HEIGHT - WALL_HEIGHT - WALL_HEIGHT
static const int FIELD_WIDTH = 954; // SCREEN_WIDTH - WALL_WIDTH - WALL_WIDTH

std::vector< MyRect* > SoccerGame::m_sRegions = std::vector< MyRect* >();
std::vector< Wall* > SoccerGame::m_sWalls = std::vector< Wall* >();

SoccerGame::SoccerGame(void)
   : m_pRedTeamPost( new GoalPosts( glm::vec2( 20.0f, 160.0f ), glm::vec2(  40.0f, 480.0f ) ) ) // TODO: Magic numbers should become constants
   , m_pBlueTeamPost( new GoalPosts( glm::vec2( 984.0f, 160.0f ), glm::vec2( 1004, 480.0f ) ) ) 
   , m_pRedTeam( new Teams( TEAM::RED, m_pRedTeamPost ) )
   , m_pBlueTeam( new Teams( TEAM::BLUE, m_pBlueTeamPost ) )
   , m_pMySoccerBall( SoccerBall::getSoccerBallInstance() )
   , m_pBackground( al_load_bitmap( "soccerPitch.png" ) )
   , m_hasInitialized( true )
   , m_isGameOn( true )
{
	m_pRedTeam->setOpponent( m_pBlueTeam );   
	m_pBlueTeam->setOpponent( m_pRedTeam );
}

SoccerGame::~SoccerGame(void)
{
   delete m_pRedTeam;
   delete m_pBlueTeam;
   al_destroy_bitmap( m_pBackground );
}

SoccerGame* SoccerGame::getGameInstance()
{ 
   static SoccerGame soccerGame; 
   return &soccerGame;
}    

void SoccerGame::initRegions()
{
   m_sWalls.reserve( 4 ); //  there will be 4 walls, start from top and go clock wise. \
   
   Wall* pTempTopWall = new Wall( glm::vec2( 0, 0 ) , glm::vec2( SCREEN_WIDTH, WALLS_HEIGHT ), glm::vec2( 0, 1 ) );
   Wall* pTempRightWall = new Wall( glm::vec2( SCREEN_WIDTH - WALLS_WIDTH, 0 ), glm::vec2( SCREEN_WIDTH, SCREEN_HEIGHT ), glm::vec2( -1, 0 ) );
   Wall* pTempBotWall = new Wall( glm::vec2( 0, SCREEN_HEIGHT - WALLS_HEIGHT ), glm::vec2( SCREEN_WIDTH, SCREEN_HEIGHT ), glm::vec2( 0, -1 ) );
   Wall* pTempLeftWall = new Wall( glm::vec2( 0, 0 ), glm::vec2( WALLS_WIDTH, SCREEN_HEIGHT ), glm::vec2( 1, 0 ) );
   m_sWalls.push_back( pTempTopWall );
   m_sWalls.push_back( pTempRightWall );
   m_sWalls.push_back( pTempBotWall );
   m_sWalls.push_back( pTempLeftWall );

   std::cout<<"INITIALIZING MAIN GAME"<<std::endl;
   m_sRegions.reserve( NUM_REGIONS );
   for( int i = 0 ; i < NUM_REGIONS ; ++i ) // 18 regions. 
   {
      switch( i % 3 )
      {
      case 0:
         {
            MyRect* tempRect = new MyRect( glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * ( i + 3 ) / NUM_REGIONS ) + WALLS_WIDTH, FIELD_HEIGHT - ( FIELD_HEIGHT / 3 ) + WALLS_HEIGHT ),
				                           glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * i / NUM_REGIONS ) + WALLS_WIDTH, FIELD_HEIGHT + WALLS_HEIGHT ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 1:
         {
            MyRect* tempRect = new MyRect( glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * ( i + 2 ) / NUM_REGIONS ) + WALLS_WIDTH, FIELD_HEIGHT - ( 2 * FIELD_HEIGHT / 3 ) + WALLS_HEIGHT ), 
				                           glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * ( i - 1 ) / NUM_REGIONS ) + WALLS_WIDTH, FIELD_HEIGHT - ( FIELD_HEIGHT / 3 ) + WALLS_HEIGHT ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 2:
         {
            MyRect* tempRect = new MyRect( glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * ( i + 1 ) / NUM_REGIONS ) + WALLS_WIDTH, 0 + WALLS_HEIGHT ), 
				                           glm::vec2( FIELD_WIDTH - ( FIELD_WIDTH * ( i-2 ) / NUM_REGIONS ) + WALLS_WIDTH, FIELD_HEIGHT - ( 2 * FIELD_HEIGHT / 3 ) + WALLS_HEIGHT ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      }
   }
   std::cout<<"INITIALIZED REGIONS"<<std::endl;
}

void SoccerGame::update()
{
   draw();
   m_pRedTeam->update();
   m_pBlueTeam->update();
   m_pMySoccerBall->update();
   m_pBlueTeamPost->checkGoal();
   m_pRedTeamPost->checkGoal();
}

void SoccerGame::draw()
{
   al_draw_bitmap( m_pBackground, 0, 0, 0 );
   m_pRedTeam->draw();
   m_pBlueTeam->draw();
   m_pMySoccerBall->draw();

   for( int i = 0 ; i < 4 ; ++i )
   {
      m_sWalls[ i ]->debugDraw();
   }
   m_pRedTeamPost->debugDraw();
   m_pBlueTeamPost->debugDraw();
   
   for( int i = 0 ; i < 18 ; ++i )
   {
	   m_sRegions[i]->debugDraw();
   }
}

void SoccerGame::paused()
{
}

bool SoccerGame::doGoalkeepersHaveBall() const 
{ 
   return ( m_pRedTeam->doesGoalKeeperHaveBall() || m_pBlueTeam->doesGoalKeeperHaveBall() );
}