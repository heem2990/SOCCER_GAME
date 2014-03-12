#pragma once
#include<glm\glm.hpp>

#define FLAG_ARRIVE ( 1<<0 );
#define FLAG_SEEK ( 1<<1 );
#define FLAG_SEPARATION ( 1<<2 );
#define FLAG_INTERPOSE ( 1<<3 );
#define FLAG_PURSUIT ( 1<<4 );

class MovingEntity;

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
   void interposeOff(){ m_steeringBehaviorsFlag &= ~FLAG_INTERPOSE; m_pInterposeTarget = NULL; m_interposePercent = 0.5; }
   void pursuitOn(){ m_steeringBehaviorsFlag |= FLAG_PURSUIT; }
   void pursuitOff(){ m_steeringBehaviorsFlag &= ~FLAG_PURSUIT; }

   // TODO check why the following commented code is returning an error. 
   bool isArriveOn(); //{ return m_steeringBehaviorsFlag & FLAG_ARRIVE ; }
   bool isPursuitOn(); //{ return m_steeringBehaviorsFlag & FLAG_PURSUIT; }
   bool isSeekOn(); //{ return m_steeringBehaviorsFlag & FLAG_SEEK; }
   bool isSeparationOn(); //{ return m_steeringBehaviorsFlag & FLAG_SEPARATION; }
   bool isInterposeOn(); //{ return m_steeringBehaviorsFlag & FLAG_INTERPOSE; }

   void setTarget( MovingEntity* target ){ m_pTarget = target; }
   void setInterPoseTarget( MovingEntity* target, float percentAway = 0.5f ){ m_pInterposeTarget = target; m_interposePercent = percentAway; }
   void setInterPoseStaticTarget( glm::vec2 staticTarget, float percentAway = 0.5f ){ m_staticInterposeTarget = staticTarget; m_interposePercent = percentAway; m_pInterposeTarget = NULL; }
   void setArriveTarget( glm::vec2 target ){ m_arriveTarget = target; }
   glm::vec2 getArriveTarget() const { return m_arriveTarget; }
   MovingEntity* getTarget() const { return m_pTarget ; }

private:

   glm::vec2 calcSeekForce( glm::vec2 target );
   glm::vec2 calcArriveVelocity( glm::vec2 target );
   glm::vec2 calcPursuitVelocity( MovingEntity* pMovingTarget );
   glm::vec2 calcInterposeVelocity( MovingEntity* pMovingTargetA , MovingEntity* pMovingTargetB );
   glm::vec2 calcInterposeVelocityStatic( MovingEntity* MovingTargetA, glm::vec2 staticTargetB );
   glm::vec2 calcSeparationForce();

   float calcTurnAroundTime( MovingEntity* pMovingTarget );

   MovingEntity* m_pOwner;
   MovingEntity* m_pTarget;
   MovingEntity* m_pInterposeTarget;
   
   glm::vec2 m_staticInterposeTarget;
   glm::vec2 m_arriveTarget;

   int m_steeringBehaviorsFlag;
   float m_interposePercent;

};
