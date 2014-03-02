#pragma once
#include "MovingEntity.h"

class SoccerBall :
   public MovingEntity
{
public:

   SoccerBall(void);
   ~SoccerBall(void);
   virtual void update(){};
   //virtual void draw(){};

private:

};

