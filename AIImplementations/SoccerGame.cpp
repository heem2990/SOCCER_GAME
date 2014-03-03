#include "SoccerGame.h"
#include<allegro5\allegro.h>
#include"Teams.h"
#include"SoccerBall.h"
#include"GoalPosts.h"
#include"MyRect.h"
#include"Constants.h"
#include<string>
#include<iostream>

std::vector< MyRect* > SoccerGame::m_sRegions = std::vector< MyRect* >();
SoccerGame::SoccerGame(void)
   : m_redTeamPost()
   , m_blueTeamPost()
   , m_redTeam( new Teams( TEAM::RED ) )
   , m_blueTeam( new Teams( TEAM::BLUE ) )
   , m_mySoccerBall( new SoccerBall() )
   , m_background( al_load_bitmap( "soccerPitch.png" ) )
{
   
}

SoccerGame::~SoccerGame(void)
{
   delete m_redTeam;
   delete m_blueTeam;
   al_destroy_bitmap( m_background );
}

void SoccerGame::initRegions()
{
   std::cout<<"INITIALIZING MAIN GAME"<<std::endl;
   m_sRegions.reserve( 18 );
   for( int i = 0 ; i < 18 ; ++i ) // 18 regions. 
   {
      switch( i % 3 )
      {
      case 0:
         {
            MyRect*  tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 3 ) / 18 ), SCREEN_HEIGHT - ( SCREEN_HEIGHT / 3 ) ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * i / 18 ), SCREEN_HEIGHT ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 1:
         {
            MyRect*  tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 2 ) / 18 ), SCREEN_HEIGHT - ( 2 * SCREEN_HEIGHT / 3 ) ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i - 1 ) / 18 ), SCREEN_HEIGHT - ( SCREEN_HEIGHT / 3 )  ) );
            m_sRegions.push_back( tempRect );
            break;
         }
      case 2:
         {
            MyRect*  tempRect = new MyRect( glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i + 1 ) / 18 ), 0 ), glm::vec2( SCREEN_WIDTH - ( SCREEN_WIDTH * ( i-2 ) / 18 ), SCREEN_HEIGHT - ( 2 * SCREEN_HEIGHT / 3 ) ) );
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
   //m_redTeam-;
   //m_blueTeam->update();
   //m_mySoccerBall->update();
   //m_blueTeamPost->checkGoal();
   //m_redTeamPost->checkGoal();
}

void SoccerGame::draw()
{
   al_draw_bitmap( m_background, 0, 0, 0 );
   m_redTeam->update();
   m_blueTeam->update();
   m_mySoccerBall->draw();
   
}

void SoccerGame::paused()
{
}