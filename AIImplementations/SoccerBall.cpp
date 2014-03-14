#include "SoccerBall.h"
#include "Constants.h"
#include "SoccerGame.h"
#include "Wall.h"
#include <iostream>
#include "Players.h"

static const int SOCCER_BALL_MAX_SPEED = 4;
static const float DECELERATION_MAGNITUDE_ON_BALL = 0.1f;
static const float SOCCER_BALL_MASS = 5.0f;

SoccerBall::SoccerBall(void)
   : MovingEntity( "soccerball.png", glm::vec2( SCREEN_WIDTH>>1, SCREEN_HEIGHT>>1 ), glm::vec2( 0, 0 ), glm::vec2( 0, 0 ), SOCCER_BALL_MAX_SPEED, SOCCER_BALL_MASS )
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
   testCollisionsWithWalls();
   glm::vec2 currVelocity = getVelocity();
   if( ( ( currVelocity.x* currVelocity.x ) + ( currVelocity.y * currVelocity.y ) ) > 0.00f )
   {
      testCollisionsWithWalls();
      currVelocity -= glm::normalize( currVelocity ) * DECELERATION_MAGNITUDE_ON_BALL;
      setVelocity( currVelocity );
   }
   //std::cout<<getPosition().x<<" "<<getPosition().y<<std::endl;
}

void SoccerBall::kick( glm::vec2 direction, float force )
{
   float speed = force/ getMass();
   glm::vec2 velocity = direction * speed;

   setVelocity( velocity );
}

void SoccerBall::trap( Players* pOwner )
{ 
   setVelocity( glm::vec2() );  
   m_pBallOwner = pOwner;
   m_pBallOwner->setHasBall( true );
}

void SoccerBall::setBallPosition( glm::vec2 position )
{
   setPosition( position );
}

float SoccerBall::timeToCoverDistance( glm::vec2 from, glm::vec2 to, float force ) const
{
   float speed = force/ getMass();

   glm::vec2 displacement = to - from;
   float distance = sqrtf( displacement.x * displacement.x + displacement.y + displacement.y ) ;
   
   float velocityAtDestination = sqrtf( speed * speed + 2* DECELERATION_MAGNITUDE_ON_BALL * distance );

   if( velocityAtDestination < 0.0f )
   {
      return -1.0f;
   }

   float time = ( velocityAtDestination - speed ) / DECELERATION_MAGNITUDE_ON_BALL;
   return time;
}

glm::vec2 SoccerBall::futurePosition( float time ) const
{
   // s = u*t + 0.5 * a *t*t;
   glm::vec2 currentVelocity = getVelocity();

   glm::vec2 distanceWithCurrentSpeed = currentVelocity * time; // u*t
   glm::vec2 distanceOpposedByFriction = 0.5f * DECELERATION_MAGNITUDE_ON_BALL * time * time * glm::normalize( currentVelocity ); // 0.5 * a *t*t;

   return ( getPosition() + distanceWithCurrentSpeed + distanceOpposedByFriction );
}

void SoccerBall::testCollisionsWithWalls()
{

   for( int i = 0 ; i < 4 ; ++i )
   {
      if( SoccerGame::getWalls()[ i ]->contains( getPosition() ) )
      {
         glm::vec2 reflectedVelocity = SoccerGame::getWalls()[ i ]->reflectAgainstNormal( getVelocity() );
         setVelocity( reflectedVelocity );
         break;
      }
   }
}