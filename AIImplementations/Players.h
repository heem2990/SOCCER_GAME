#pragma once
#include"MovingEntity.h"
#include"StateMachine.h"
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>

static const char* teamImages[ 2 ]  = { "bluePlayer.png", "redPlayer.png" };
  
struct TEAM
{
   enum id
   {
      BLUE, 
      RED, 

      NUM_TEAMS
   };
};

struct PlayerPositions
{
   enum id
   {
      GOALKEEPER,
      DEFENSE_LEFT,
      DEFENSE_RIGHT,
      OFFENSE_LEFT,
      OFFENSE_RIGHT,

      NUM_POSITIONS,
   };
};

class Players :
   public MovingEntity
{

public:
   Players( TEAM::id myTeam, PlayerPositions::id );
   ~Players(void);
   void draw();
   void update();

private:

   TEAM::id m_myTeam;
   bool m_bHasBall;
   StateMachine<Players>* m_myStateMachine;   
   ALLEGRO_FONT* m_playerStateFont;
   int m_homeRegion;
};

