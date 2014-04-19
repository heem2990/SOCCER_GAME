// Base class for all the players. It handles all the common functionalities of a field player and a goalkeeper. 
#pragma once
#include"MovingEntity.h"
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

struct PlayerPositions // Used to assign different roles to the players.
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
   virtual bool handleMessage( const Message& msg );

   bool isPlayerHome();
   bool isInKickingRangeOfTheBall() const; 
   bool isAtTarget() const;
   bool isAtArriveTarget() const;
   bool isPlayerClosestToBall() const { return m_isClosestPlayerToBall; }
   bool isPlayerControllingTheBall() const { return m_bHasBall; }
   bool isPlayerAheadOfAttacker() const;
   bool isPlayerWithinReceivingRange() const; // should be a const function, but is not because we are calculating the sqrMag manually in there. CHANGE  
   bool isBallWithinInterceptRanger();
   void setIsClosestToBall( bool close ){ m_isClosestPlayerToBall = close; }
   bool isThreatened() const;
   SteeringBehaviors* getSteeringBehavior() const { return m_pSteeringBehavior; }
   Teams* getMyTeam() const { return m_pMyTeam; }

   void setHomeRegionAsTarget() const;
   void setHasBall( bool hasBall );
   void findSupportingPlayer();

private:
	
   SteeringBehaviors* m_pSteeringBehavior;
   Teams* m_pMyTeam;

   const TEAM::id m_myTeamColor;
   bool m_bHasBall; 
   bool m_isClosestPlayerToBall;

   int m_homeRegion;
};

