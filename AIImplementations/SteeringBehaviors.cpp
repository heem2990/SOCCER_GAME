#include "SteeringBehaviors.h"
#include <math.h>
#include "BaseGameEntity.h"
#include "MovingEntity.h"

static const double DECELERATION = 2;
static const double TURN_AROUND_SPEED = 0.5;

double sqrmag( glm::vec2 currvector )
{
	return ( currvector.x * currvector.x + currvector.y * currvector.y );
}

SteeringBehaviors::SteeringBehaviors( MovingEntity* pOwner )
   : m_pOwner( pOwner )
{
}

void SteeringBehaviors::calculateForce()
{
}

glm::vec2 SteeringBehaviors::calcArriveForce()
{
   glm::vec2 velocityToTarget = m_pTarget->getPosition() - m_pOwner->getPosition();
   double distanceToTarget = sqrt( sqrmag( velocityToTarget ) );

   if( distanceToTarget > 0.0f )
   {
      const double decelarationTweaker = 0.3;
      double initialSpeed = sqrt( 2 * distanceToTarget * DECELERATION );  // TODO : Maybe allow custom deceleration?
      initialSpeed = min( initialSpeed , m_pOwner->getMaxSpeed() );
      glm::vec2 velocityRequired = static_cast< float>( initialSpeed ) * velocityToTarget;
      return ( velocityRequired - m_pOwner->getVelocity() );
   }

   return glm::vec2();
}

glm::vec2 SteeringBehaviors::calcSeekForce( glm::vec2 target )
{
   glm::vec2 velocityToTarget = target - m_pOwner->getPosition();
   velocityToTarget = ( static_cast< float > ( m_pOwner->getMaxSpeed() ) ) * glm::normalize( velocityToTarget ) ;
   return ( velocityToTarget - m_pOwner->getVelocity() );
}

glm::vec2 SteeringBehaviors::calcInterposeForce()
{

   return glm::vec2();
}

glm::vec2 SteeringBehaviors::calcPursuitForce( MovingEntity* movingTarget )
{
   glm::vec2 toTarget =  movingTarget->getPosition() - m_pOwner->getPosition();

   double relativeHeading = glm::dot( m_pOwner->getHeading(), movingTarget->getHeading() );
   if( ( glm::dot( m_pOwner->getHeading(), toTarget ) > 0 ) // this ensures that the vehical is in the same direction as the vector from owner to target
              && relativeHeading < -0.95 ) // this ensures that the owner and target are facing the opposite direction. 
   {
      return calcSeekForce( movingTarget->getPosition() );
   }

   double turnAroundTime = calcTurnAroundTime( movingTarget ) + ( sqrt( sqrmag( toTarget ) ) / ( m_pOwner->getMaxSpeed() + movingTarget->getCurrentSpeed() ) );

   return calcSeekForce( ( movingTarget->getPosition() ) + ( movingTarget->getVelocity() * static_cast< float >( turnAroundTime ) ) ); // seeking a point which is at currentPosition + ( time*velocity )
}

double SteeringBehaviors::calcTurnAroundTime( MovingEntity* movingTarget )
{
   glm::vec2 toTarget = glm::normalize( movingTarget->getPosition() - m_pOwner->getPosition() );
   double dotPro = glm::dot( toTarget, m_pOwner->getHeading() );

   return( ( dotPro - 1 ) * TURN_AROUND_SPEED * -1 );
}

glm::vec2 SteeringBehaviors::calcSeparationForce()
{
   return glm::vec2();
}

bool SteeringBehaviors::isArriveOn()
{
   int temp = m_steeringBehaviorsFlag & FLAG_ARRIVE;
   if( temp == 0 )
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
   if( temp == 0 )
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
   if( temp == 0 )
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
   if( temp == 0 )
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
   if( temp == 0 )
   {
      return true;
   }
   else
   {
      return false;
   }
}