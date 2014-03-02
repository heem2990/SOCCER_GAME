/**
This class is not used. It was created basically for testing purposes , and to get started with a basic code structure for the implementation. 
**/
#pragma once
#include "MovingEntity.h"

typedef int ( *steeringBehaviour)( MovingEntity* ) ;

class Agent :  public MovingEntity
{
public:
	Agent( char* imageName, glm::vec2 startingPosition, glm::vec2 startingVelocity, MovingEntity* target );
   ~Agent(void);
   glm::vec2 seek();
   glm::vec2 flee();
   glm::vec2 pursue();

private:
	MovingEntity* m_myTarget;
	steeringBehaviour myBehavior;

};

