#pragma once
#include "MovingEntity.h"

class Players;

class SoccerBall :
   public MovingEntity
{
public:
   
   static SoccerBall* getSoccerBallInstance();

   void kick( glm::vec2 direction, float force );
   void trap( Players* pOwner );
   void setBallPosition( glm::vec2 position );

   float timeToCoverDistance( glm::vec2 from, glm::vec2 to, float force ) const;
   glm::vec2 futurePosition( float time ) const;
   virtual void update();

private:
   SoccerBall(void);
   ~SoccerBall(void);

   void testCollisionsWithWalls();
   
   Players* m_pBallOwner;

};

