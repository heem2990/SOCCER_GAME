/**
This class is not used. It was created basically for testing purposes , and to get started with a basic code structure for the implementation. 
**/
#include "Agent.h"
#include<glm\glm.hpp>
#include<iostream>

Agent::Agent( char* imageName, glm::vec2 startingPosition, glm::vec2 startingVelocity, MovingEntity* target )
   : MovingEntity( imageName, startingPosition, startingVelocity, glm::vec2() )
   , m_myTarget( target )
{
}

Agent::~Agent(void)
{
}

glm::vec2 Agent::seek()
{
	glm::vec2 desiredVelocity = 10.0f * glm::normalize( m_myTarget->getPosition() - getPosition() );
    
	setVelocity( desiredVelocity );
	return desiredVelocity;
}

glm::vec2 Agent::flee()
{
	glm::vec2 desiredVelocity = m_myTarget->getPosition() - getPosition();
	float sqrMag = desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y;
	if( sqrMag < 5000.0f )
	{
		glm::vec2 direction = glm::normalize( glm::vec2( desiredVelocity.x * -1.0f, desiredVelocity.y * -1.0f ) );
		glm::vec2 velo = glm::vec2( direction.x * 10, direction.y * 10 );
		setVelocity( velo );
	}
   return glm::vec2();
}

glm::vec2 Agent::pursue()
{
   return glm::vec2();
}