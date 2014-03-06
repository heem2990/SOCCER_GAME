#pragma once
#include<allegro5\allegro.h>
#include<vector>
#include"MyRect.h"

//class MyRect;
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
   bool isGameOn() const{ return m_isGameOn; }
   bool doGoalkeepersHaveBall() const ;
private:
   
   static std::vector< MyRect* > m_sRegions;

   GoalPosts* m_redTeamPost;
   GoalPosts* m_blueTeamPost;
   Teams* m_redTeam;
   Teams* m_blueTeam;
   SoccerBall* m_mySoccerBall;
   ALLEGRO_BITMAP* m_background;
   gameState m_stateFunction;

   bool m_hasInitialized;
   bool m_isGameOn;
};

