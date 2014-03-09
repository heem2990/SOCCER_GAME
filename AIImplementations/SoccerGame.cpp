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

std::vector< MyRect* > SoccerGame::m_sRegions = std::vector< MyRect* >();
std::vector< Wall* > SoccerGame::m_sWalls = std::vector< Wall* >();

SoccerGame::SoccerGame(void)
   : m_redTeamPost()
   , m_blueTeamPost()
   , m_redTeam( new Teams( TEAM::RED ) )
   , m_blueTeam( new Teams( TEAM::BLUE ) )
   , m_mySoccerBall( SoccerBall::getSoccerBallInstance() )
   , m_background( al_load_bitmap( "soccerPitch.png" ) )
{
	m_redTeam->setOpponent( m_blueTeam );   
	m_blueTeam->setOpponent( m_redTeam );
}

SoccerGame::~SoccerGame(void)
{
   delete m_redTeam;
   delete m_blueTeam;
   al_destroy_bitmap( m_background );
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
            MyRect* tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 3 ) / NUM_REGIONS ), SCREEN_HEIGHT - ( SCREEN_HEIGHT / 3 ) ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * i / NUM_REGIONS ), SCREEN_HEIGHT ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 1:
         {
            MyRect* tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 2 ) / NUM_REGIONS ), SCREEN_HEIGHT - ( 2 * SCREEN_HEIGHT / 3 ) ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i - 1 ) / NUM_REGIONS ), SCREEN_HEIGHT - ( SCREEN_HEIGHT / 3 )  ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 2:
         {
            MyRect* tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 1 ) / NUM_REGIONS ), 0 ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i-2 ) / NUM_REGIONS ), SCREEN_HEIGHT - ( 2 * SCREEN_HEIGHT / 3 ) ) );
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
   m_redTeam->update();
   m_blueTeam->update();
   m_mySoccerBall->update();
   //m_blueTeamPost->checkGoal();
   //m_redTeamPost->checkGoal();
}

void SoccerGame::draw()
{
   al_draw_bitmap( m_background, 0, 0, 0 );
   m_redTeam->draw();
   m_blueTeam->draw();
   m_mySoccerBall->draw();

   for( int i = 0 ; i < 4 ; ++i )
   {
      m_sWalls[ i ]->debugDraw();
   }
   
}

void SoccerGame::paused()
{
}

bool SoccerGame::doGoalkeepersHaveBall() const 
{ 
   return ( m_redTeam->doesGoalKeeperHaveBall() || m_blueTeam->doesGoalKeeperHaveBall() );
}