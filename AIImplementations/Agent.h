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

