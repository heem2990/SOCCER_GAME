#include "SoccerBall.h"
#include"Constants.h"
static const int SOCCER_BALL_MAX_SPEED = 4;
SoccerBall::SoccerBall(void)
   : MovingEntity( "soccerball.png", glm::vec2( SCREEN_WIDTH>>1, SCREEN_HEIGHT>>1 ), glm::vec2( 0, 0 ), glm::vec2( 0, 0 ), SOCCER_BALL_MAX_SPEED )
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

void SoccerBall::update()
{
	MovingEntity::update();
}

void SoccerBall::draw()
{
	MovingEntity::draw();
}
