#pragma once
#include<allegro5\allegro.h>
#include<vector>
// Singleton class for the main game. It has the main update loop. The object for this class is used in main.cpp. 
#include"MyRect.h"

class Wall;
class GoalPosts;
class Teams;
class SoccerBall;

class SoccerGame
{
   typedef void ( SoccerGame::*gameState )();
public:

   SoccerGame(void);
   ~SoccerGame(void);
   
   static void initRegions();
   void update();
   void draw();
   void paused();

   static SoccerGame* getGameInstance(); 
   inline static std::vector< MyRect* > getRegions(){ return m_sRegions; }
   inline static std::vector< Wall* > getWalls(){ return m_sWalls; }
   void setGameOn( bool isOn ) { ms_bIsGameOn = isOn; }
   bool isGameOn() const { return ms_bIsGameOn; }
   bool doGoalkeepersHaveBall() const ;

private:
   
   static std::vector< MyRect* > m_sRegions;
   static std::vector< Wall* > m_sWalls;

   GoalPosts* m_pRedTeamPost;
   GoalPosts* m_pBlueTeamPost;
   Teams* m_pRedTeam;
   Teams* m_pBlueTeam;
   SoccerBall* m_pMySoccerBall;
   ALLEGRO_BITMAP* m_pBackground;

   bool m_hasInitialized;
   static bool ms_bIsGameOn;
};

