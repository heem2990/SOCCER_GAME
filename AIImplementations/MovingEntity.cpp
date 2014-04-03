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

MovingEntity::MovingEntity( char* imageName, glm::vec2 startingPosition, glm::vec2 startingVelocity , glm::vec2 heading, float maxSpeed, float mass )
   : BaseGameEntity( imageName,  startingPosition )
   , m_lookAtTarget( NULL )
   , m_heading( heading )
   , m_velocity( startingVelocity )
   , m_acceleration( glm::vec2() )
   , m_force( glm::vec2() )
   , m_side( glm::vec2() )
   , m_width( 15 )
   , m_height( 15 )	
   , m_mass( mass )
   , m_maxSpeed( maxSpeed )
   , m_lookAt( 0 )
{
}
 
MovingEntity::~MovingEntity(void)
{
}

void MovingEntity::draw()
{
   // Just to handle the current angle the sprite should be drawn at. since tan(90) is not defined, we check for it specifically.
   float angle = ( m_heading.x == 0 )? 3.1415/2:atan2( m_heading.y, m_heading.x );
   al_draw_rotated_bitmap( getImage(), 0, 0, getPosition().x, getPosition().y, angle + ( 3.1415f/2 ), 0 ); // adding 90 degrees to align it to +x and +y
}

void MovingEntity::update()
{
   m_acceleration = glm::vec2( m_force.x / m_mass, m_force.y / m_mass  ) ;
   m_velocity += m_acceleration; // adding instantaneous acceleration to current velocity. 
   glm::vec2 newPosition = getPosition() + m_velocity;
   
   setPosition( newPosition ); 
   int lookatTemp = m_lookAt & LOOK_AT // checking to see, if the entity should look at something specific. 

   if( lookatTemp != 0 && m_lookAtTarget )
   {
	   m_heading = glm::normalize( m_lookAtTarget->getPosition() - getPosition() );
   }
   else if( sqrMag( m_velocity ) > 0.01f )// we check this to avoid div by 0.and then change heading to look in direction of velocity. 
   {
	   m_heading = glm::normalize( m_velocity );
	   m_side = glm::vec2( m_heading.y , -1 * m_heading.x );
   }

}

bool MovingEntity::handleMessage( const Message& msg )
{
   return false; // TODO: Should return whether the message has been handled successfull or not!
}

double MovingEntity::getCurrentSpeed() const
{
   return( sqrt( sqrMag( m_velocity ) ) );
}

void MovingEntity::setLookAtTarget( MovingEntity* target )
{
	m_lookAt |= LOOK_AT;
	m_lookAtTarget = target;
}