#include "MovingEntity.h"
#include<glm\glm.hpp>
#include<iostream>
#include<math.h>
#include"Constants.h"

static const double MAX_FORCE = 10.0f;
static const double MAX_VELOCITY = 10.0f;

// TODO: Move the following somehwere else
double sqrMag( glm::vec2 currVector )
{
	return ( currVector.x * currVector.x + currVector.y * currVector.y );
}

MovingEntity::MovingEntity( char* imageName, glm::vec2 startingPosition, glm::vec2 startingVelocity , glm::vec2 heading, int maxSpeed )
   : BaseGameEntity( imageName,  startingPosition )
   , m_heading( heading )
   , m_velocity( startingVelocity )
   , m_acceleration()
   , m_force()
   , m_side()
   , m_width( 15 )
   , m_height( 15 )	
   , m_mass( 1 )
   , m_maxSpeed( maxSpeed )
{
}
 
MovingEntity::~MovingEntity(void)
{
}

void MovingEntity::draw()
{
   float angle = ( m_heading.x == 0 )? 3.1415/2:atan2( m_heading.y, m_heading.x );
   al_draw_rotated_bitmap( getImage(), 0, 0, getPosition().x, getPosition().y, angle + ( 3.1415f/2 ), 0 ); // adding 90 degrees to align it to +x and +y
   //al_draw_bitmap( getImage(), getPosition().x, getPosition().y, 0 );
}

void MovingEntity::update()
{
   m_acceleration = glm::vec2( m_force.x / m_mass, m_force.y / m_mass  );
   m_velocity += m_acceleration;
   glm::vec2 newPosition = getPosition() + m_velocity;
   
   // Checking for warp
   {
      newPosition.x = ( newPosition.x > SCREEN_WIDTH )? 0 : newPosition.x;
      newPosition.y = ( newPosition.y > SCREEN_HEIGHT )? 0 : newPosition.y;
      newPosition.x = ( newPosition.x < 0 )? SCREEN_WIDTH : newPosition.x;
      newPosition.y = ( newPosition.y < 0 )? SCREEN_HEIGHT : newPosition.y;
      setPosition( newPosition ); 
   }
 
   if( sqrMag( m_velocity ) > 5.0f )
   {
	   m_heading = glm::normalize( m_velocity );
	   m_side = glm::vec2( m_heading.y , -1 * m_heading.x );
   }
   draw();
}

bool MovingEntity::handleMessage( const Message& msg )
{
   return true; // TODO: Should return whether the message has been handled successfull or not!
}

double MovingEntity::getCurrentSpeed() const
{
   return( sqrt( sqrMag( m_velocity ) ) );
}