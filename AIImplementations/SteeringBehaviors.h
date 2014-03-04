#pragma once
#include<glm\glm.hpp>

#define FLAG_ARRIVE ( 1<<0 );
#define FLAG_SEEK ( 1<<1 );
#define FLAG_SEPARATION ( 1<<2 );
#define FLAG_INTERPOSE ( 1<<3 );
#define FLAG_PURSUIT ( 1<<4 );

class MovingEntity;
class BaseGameEntity;

class SteeringBehaviors
{
public:
   SteeringBehaviors( MovingEntity* pOwner );

   void calculateForce();

   void arriveOn(){ m_steeringBehaviorsFlag |= FLAG_ARRIVE; }
   void arriveOff(){ m_steeringBehaviorsFlag &= ~FLAG_ARRIVE; }
   void seekOn(){ m_steeringBehaviorsFlag |= FLAG_SEEK; }
   void seekOff(){ m_steeringBehaviorsFlag &= ~FLAG_SEEK; }
   void separationOn(){ m_steeringBehaviorsFlag |= FLAG_SEPARATION; }
   void separationOff(){ m_steeringBehaviorsFlag &= ~FLAG_SEPARATION; }
   void interposeOn(){ m_steeringBehaviorsFlag |= FLAG_INTERPOSE; }
   void interposeOff(){ m_steeringBehaviorsFlag &= ~FLAG_INTERPOSE; }
   void pursuitOn(){ m_steeringBehaviorsFlag |= FLAG_PURSUIT; }
   void pursuitOff(){ m_steeringBehaviorsFlag &= ~FLAG_PURSUIT; }

   bool isArriveOn(); //{ return m_steeringBehaviorsFlag & FLAG_ARRIVE ; }
   bool isPusuitOn(); //{ return m_steeringBehaviorsFlag & FLAG_PURSUIT; }
   bool isSeekOn(); //{ return m_steeringBehaviorsFlag & FLAG_SEEK; }
   bool isSeparationOn(); //{ return m_steeringBehaviorsFlag & FLAG_SEPARATION; }
   bool isInterposeOn(); //{ return m_steeringBehaviorsFlag & FLAG_INTERPOSE; }

private:

   glm::vec2 calcSeekForce( glm::vec2 target );
   glm::vec2 calcArriveForce( glm::vec2 target );
   glm::vec2 calcPursuitForce( MovingEntity* pMovingTarget );
   glm::vec2 calcInterposeForce( MovingEntity* pMovingTargetA , MovingEntity* pMovingTargetB );
   glm::vec2 calcSeparationForce();

   float calcTurnAroundTime( MovingEntity* pMovingTarget );

   MovingEntity* m_pOwner;
   BaseGameEntity* m_pTarget;

   int m_steeringBehaviorsFlag;

};
