#pragma once
#include "BaseGameEntity.h"

class MovingEntity :
	public BaseGameEntity
{
public:
	MovingEntity( char* imageName, glm::vec2 startingPosition, glm::vec2 startingVelocity, glm::vec2 heading );
	~MovingEntity(void);

   int getHeight() const {  return m_height; }
   int getWidth() const { return m_width; }

   glm::vec2 getVelocity() const { return m_velocity; }
   glm::vec2 getAcceleration() const { return m_acceleration; }
   glm::vec2 getForce() const { return m_force; }

   void setVelocity( glm::vec2 velocity ){ m_velocity = velocity; };
   void setAccelereration( glm::vec2 acceleration ){ m_acceleration = acceleration; };
   void setForce( glm::vec2 force ){ m_force = force; };
   glm::vec2 getTarget() const { return m_myTarget; }

   virtual void draw();
   virtual void update();
   virtual bool handleMessage( const Message& msg );

private:

   glm::vec2 m_myTarget; // TODO: MAKE IT A BASEGAME ENTITY;
	glm::vec2 m_heading;
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;
	glm::vec2 m_force;
	glm::vec2 m_side;
	
	int m_width;
   int m_height;	
	int m_mass;

};

