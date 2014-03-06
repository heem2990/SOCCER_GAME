#pragma once
#include"MovingEntity.h"
#include"StateMachine.h"
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>

static const char* teamImages[ 2 ]  = { "bluePlayer.png", "redPlayer.png" };

class SteeringBehaviors;

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

   bool isPlayerHome();
   bool isInKickingRangeOfTheBall();

   StateMachine< Players >* getStateMachine() const { return m_pMyStateMachine; }
   SteeringBehaviors* getSteeringBehavior() const { return m_pSteeringBehavior; }

   bool isPlayerClosestToBall() const { return m_isClosestPlayerToBall; }

private:
	
   ALLEGRO_FONT* m_playerStateFont;
   TEAM::id m_myTeam;
   StateMachine< Players >* m_pMyStateMachine;  
   SteeringBehaviors* m_pSteeringBehavior;

   bool m_bHasBall; 
   bool m_isClosestPlayerToBall;

   int m_homeRegion;
};

