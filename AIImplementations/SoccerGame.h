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

   inline static SoccerGame* getGameInstance(){ return m_soccerGame; }   
   inline static std::vector< MyRect* > getRegions(){ return m_sRegions; }

private:
   
   static std::vector< MyRect* > m_sRegions;
   static SoccerGame* m_soccerGame;

   GoalPosts* m_redTeamPost;
   GoalPosts* m_blueTeamPost;
   Teams* m_redTeam;
   Teams* m_blueTeam;
   SoccerBall* m_mySoccerBall;
   ALLEGRO_BITMAP* m_background;
   gameState m_stateFunction;

   bool m_hasInitialized;
};

