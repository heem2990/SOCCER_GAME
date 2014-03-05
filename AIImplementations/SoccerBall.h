#pragma once
#include "MovingEntity.h"

class SoccerBall :
   public MovingEntity
{
public:

	virtual void update();
   virtual void draw();
   static SoccerBall* getSoccerBallInstance();
private:
   SoccerBall(void);
   ~SoccerBall(void);

};

