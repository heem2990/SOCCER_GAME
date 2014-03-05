#include "SoccerBall.h"
#include"Constants.h"

SoccerBall::SoccerBall(void)
   : MovingEntity( "soccerball.png", glm::vec2( SCREEN_WIDTH>>1, SCREEN_HEIGHT>>1 ), glm::vec2(), glm::vec2() )
{
}


SoccerBall::~SoccerBall(void)
{
}

SoccerBall* SoccerBall::getSoccerBallInstance()
{
	static SoccerBall pBall;
	return &pBall;
}