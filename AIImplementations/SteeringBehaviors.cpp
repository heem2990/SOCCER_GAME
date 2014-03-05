#include "SteeringBehaviors.h"
#include <math.h>
#include <iostream>
#include "BaseGameEntity.h"
#include "MovingEntity.h"

static const float DECELERATION = 2;
static const float TURN_AROUND_SPEED = 0.5;

float sqrmag( glm::vec2 currvector )
{
	return ( currvector.x * currvector.x + currvector.y * currvector.y );
}

SteeringBehaviors::SteeringBehaviors( MovingEntity* pOwner )
   : m_pOwner( pOwner )
{
}

void SteeringBehaviors::calculateForce()
{
	glm::vec2 force = calcArriveForce( glm::vec2( 300, 300 ) );
	m_pOwner->setForce( force ); 
}

glm::vec2 SteeringBehaviors::calcArriveForce( glm::vec2 target )
{
   glm::vec2 velocityToTarget = target - m_pOwner->getPosition();
   float distanceToTarget = sqrt( sqrmag( velocityToTarget ) );
   std::cout<<velocityToTarget.x<<" "<<velocityToTarget.y <<std::endl;
   
   if( distanceToTarget > 0.5f )
   {
      const float decelarationTweaker = 0.3;
      float initialSpeed = sqrt( 2 * distanceToTarget * 0.005 );  // TODO : Maybe allow custom deceleration?
      initialSpeed = min( initialSpeed , m_pOwner->getMaxSpeed() );
      glm::vec2 velocityRequired = static_cast< float>( initialSpeed ) * velocityToTarget;
      return ( velocityRequired - m_pOwner->getVelocity() );
   }  
   
   return glm::vec2();
}

glm::vec2 SteeringBehaviors::calcSeekForce( glm::vec2 target )
{
   glm::vec2 velocityToTarget = target - m_pOwner->getPosition();
   std::cout<<" Velocity x = "<<velocityToTarget.x << " y = "<<velocityToTarget.y<<std::endl;
   std::cout<<" Normalized Velocity x = "<<glm::normalize( velocityToTarget ).x << " y = "<<glm::normalize( velocityToTarget ).y<<std::endl;
   velocityToTarget = ( static_cast< float > ( m_pOwner->getMaxSpeed() ) ) * glm::normalize( velocityToTarget ) ;
   return ( velocityToTarget - m_pOwner->getVelocity() );
}

glm::vec2 SteeringBehaviors::calcInterposeForce( MovingEntity* pMovingTargetA , MovingEntity* pMovingTargetB )
{
   glm::vec2 midPoint = ( pMovingTargetA->getPosition() + pMovingTargetB->getPosition() )/ 2.0f;
   float timeToReachMidPoint = sqrtf( sqrmag( midPoint - m_pOwner->getPosition() ) ) / m_pOwner->getMaxSpeed();

   glm::vec2 futureTargetAPos = pMovingTargetA->getPosition() + ( pMovingTargetA->getVelocity() * timeToReachMidPoint ) ;
   glm::vec2 futureTargetBPos = pMovingTargetB->getPosition() + ( pMovingTargetB->getVelocity() * timeToReachMidPoint ) ;
   glm::vec2 futureMidPoint = ( futureTargetAPos + futureTargetBPos ) / 2.0f;

   return calcArriveForce( futureMidPoint );
}

glm::vec2 SteeringBehaviors::calcPursuitForce( MovingEntity* pMovingTarget )
{
   glm::vec2 toTarget =  pMovingTarget->getPosition() - m_pOwner->getPosition();

   float relativeHeading = glm::dot( m_pOwner->getHeading(), pMovingTarget->getHeading() );
   if( ( glm::dot( m_pOwner->getHeading(), toTarget ) > 0 ) // this ensures that the vehical is in the same direction as the vector from owner to target
              && relativeHeading < -0.95 ) // this ensures that the owner and target are facing the opposite direction. 
   {
      return calcSeekForce( pMovingTarget->getPosition() );
   }

   float turnAroundTime = calcTurnAroundTime( pMovingTarget ) + ( sqrt( sqrmag( toTarget ) ) / ( m_pOwner->getMaxSpeed() + pMovingTarget->getCurrentSpeed() ) );

   return calcSeekForce( ( pMovingTarget->getPosition() ) + ( pMovingTarget->getVelocity() * static_cast< float >( turnAroundTime ) ) ); // seeking a point which is at currentPosition + ( time*velocity )
}

float SteeringBehaviors::calcTurnAroundTime( MovingEntity* pMovingTarget )
{
   glm::vec2 toTarget = glm::normalize( pMovingTarget->getPosition() - m_pOwner->getPosition() );
   float dotPro = glm::dot( toTarget, m_pOwner->getHeading() );

   return( ( dotPro - 1 ) * TURN_AROUND_SPEED * -1 );
}

glm::vec2 SteeringBehaviors::calcSeparationForce()
{
   return glm::vec2();
}

bool SteeringBehaviors::isArriveOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_ARRIVE;
   if( temp != 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool SteeringBehaviors::isInterposeOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_INTERPOSE;
   if( temp != 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool SteeringBehaviors::isSeekOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_SEEK;
   if( temp != 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool SteeringBehaviors::isPusuitOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_PURSUIT;
   if( temp != 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool SteeringBehaviors::isSeparationOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_SEPARATION;
   if( temp != 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}