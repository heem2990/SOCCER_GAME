#include "SteeringBehaviors.h"
#include <math.h>
#include <iostream>
#include "BaseGameEntity.h"
#include "MovingEntity.h"
#include "SoccerBall.h"

static const float DECELERATION = 2;
static const float TURN_AROUND_SPEED = 0.5;
static const float SLOW_DOWN_RADIUS = 10.0;

float sqrmag( glm::vec2 currvector )
{
	return ( ( currvector.x * currvector.x ) + ( currvector.y * currvector.y ) );
}

SteeringBehaviors::SteeringBehaviors( MovingEntity* pOwner )
   : m_pOwner( pOwner )
   , m_pTarget( NULL )
   , m_arriveTarget( glm::vec2() )
   , m_steeringBehaviorsFlag( 0 )
{
}

void SteeringBehaviors::calculateForce()
{
	glm::vec2 totalVelocity = glm::vec2();
	glm::vec2 totalForce = glm::vec2();
	if( isSeekOn() )
	{
		totalForce += calcSeekForce( m_pTarget->getPosition() );
	}
	if( isArriveOn() )
	{
		totalVelocity += calcArriveVelocity( m_arriveTarget );
	}
	if( isInterposeOn() )
	{
		totalVelocity += calcInterposeVelocity( SoccerBall::getSoccerBallInstance(), m_pTarget );
	}
	if( isPusuitOn() )
	{
		totalVelocity += calcPursuitVelocity( m_pTarget );
	}
}

glm::vec2 SteeringBehaviors::calcArriveVelocity( glm::vec2 target ) 
{
   float timeToArrive = 1;
   glm::vec2 velocityToTarget = /*m_pTarget->getPosition()*/target - m_pOwner->getPosition();
   float distanceToTarget = sqrt( sqrmag( velocityToTarget ) );
   float speed = 0.0f;
   if( distanceToTarget < 1.0f )
   {
      return glm::vec2( 0, 0 );
   }

   if( distanceToTarget > SLOW_DOWN_RADIUS )
   {
      speed = m_pOwner->getMaxSpeed();
   }
   else
   {
      speed = m_pOwner->getMaxSpeed() * distanceToTarget/ 10.0f; 
   }
   return( glm::normalize( velocityToTarget ) * speed );
}

glm::vec2 SteeringBehaviors::calcSeekForce( glm::vec2 target )// this should be set as a force. Why? 
{
   glm::vec2 velocityToTarget = target - m_pOwner->getPosition();
   velocityToTarget = ( static_cast< float > ( 10 ) ) * glm::normalize( velocityToTarget ) ;
   return ( velocityToTarget - m_pOwner->getVelocity() );
}

glm::vec2 SteeringBehaviors::calcInterposeVelocity( MovingEntity* pMovingTargetA , MovingEntity* pMovingTargetB )
{
   glm::vec2 midPoint = ( pMovingTargetA->getPosition() + pMovingTargetB->getPosition() )/ 2.0f;
   float timeToReachMidPoint = sqrtf( sqrmag( midPoint - m_pOwner->getPosition() ) ) / m_pOwner->getMaxSpeed();

   glm::vec2 futureTargetAPos = pMovingTargetA->getPosition() + ( pMovingTargetA->getVelocity() * timeToReachMidPoint ) ;
   glm::vec2 futureTargetBPos = pMovingTargetB->getPosition() + ( pMovingTargetB->getVelocity() * timeToReachMidPoint ) ;
   glm::vec2 futureMidPoint = ( futureTargetAPos + futureTargetBPos ) / 2.0f;

   return calcArriveVelocity( futureMidPoint );
}

glm::vec2 SteeringBehaviors::calcPursuitVelocity( MovingEntity* pMovingTarget )
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