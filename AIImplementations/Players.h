#pragma once
#include"MovingEntity.h"
#include"StateMachine.h"
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>

static const char* teamImages[ 2 ]  = { "bluePlayer.png", "redPlayer.png" };

class Teams;
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
   Players( Teams* myTeam, PlayerPositions::id );
   ~Players(void);
   void draw();
   void update();

   bool isPlayerHome();
   bool isInKickingRangeOfTheBall();
   bool isAtTarget();
   bool isPlayerClosestToBall() const { return m_isClosestPlayerToBall; }
   bool isPlayerControllingTheBall() const { return m_bHasBall; }
   bool isPlayerAheadOfAttacker();

   StateMachine< Players >* getStateMachine() const { return m_pMyStateMachine; }
   SteeringBehaviors* getSteeringBehavior() const { return m_pSteeringBehavior; }
   Teams* getMyTeam() const { return m_pMyTeam; }

private:
	
   ALLEGRO_FONT* m_playerStateFont;
   StateMachine< Players >* m_pMyStateMachine;  
   SteeringBehaviors* m_pSteeringBehavior;
   Teams* m_pMyTeam;

   TEAM::id m_myTeamColor;
   bool m_bHasBall; 
   bool m_isClosestPlayerToBall;

   int m_homeRegion;
};

