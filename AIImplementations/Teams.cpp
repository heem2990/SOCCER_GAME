#include "Teams.h"
#include "GoalKeeper.h"
#include "Players.h"
#include "FieldPlayers.h"
#include "StateMachine.h"
#include "TeamStates.h"
#include <iostream>
#include "Teams.h"
#include "SteeringBehaviors.h"
#include "GoalPosts.h"
#include "FieldPlayersState.h"
#include "GoalKeeperStates.h"
#include "MessageDispatcher.h"
#include "SupportSpotCalculator.h"
#include "SoccerBall.h"
#include <stdlib.h>
#include <allegro5\allegro_primitives.h>

static const char* TEAMS_NAME[2] = 
{
	"Blue",
	"Red"
};
static const int TOTAL_PLAYERS = 4;

glm::vec2 toLocalPos( glm::vec2 position, glm::vec2 axis, glm::vec2 vectorToConvert )
{
   glm::vec2 toPosition = vectorToConvert - position; // V
   glm::vec2 normalizedAxis = glm::normalize( axis ); // A unity vector
   glm::vec2 toPositionNormalized = glm::normalize( toPosition ); // V, unit vector
   float magOfPositionVec = sqrtf( toPosition.x * toPosition.x + toPosition.y * toPosition.y ); // = |V|

   float sinX = normalizedAxis.y; // sin( theta ) theta is the angle of new axis with original axis
   float cosX = normalizedAxis.x;
   
   float sinY = toPositionNormalized.y; // sin(alpha) alpha is the angle of V with original axis
   float cosY = toPositionNormalized.x;

   float xOfUnit = cosY * cosX + sinY * sinX;
   float yOfUnit = sinY * cosX - sinX * cosY;

   glm::vec2 localPositionUnitVec( xOfUnit, yOfUnit );

   glm::vec2 localPosition = localPositionUnitVec * magOfPositionVec;
   return localPosition;
}

Teams::Teams( TEAM::id myTeam, GoalPosts* pMyGoalPost )
   : m_myTeam( myTeam )
   , m_playersOnTeam()
   , m_pGoalkeeper( new GoalKeeper( this ) )
   , m_pPlayerWithBall( NULL )
   , m_pSupportingPlayer( NULL )
   , m_pPlayerClosestToBall( NULL )
   , m_pPlayerReceivingPass( NULL )
   , m_pOpponent( NULL )
   , m_pMyGoalPost( pMyGoalPost )
   , m_pSupportSpotCalculator( new SupportSpotCalculator( this ) )
   , m_hasBall( false )   
   , m_pMyStateMachine( new StateMachine< Teams >( this ) )
{
   for( int i = 0 ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam.push_back( new FieldPlayers( this, ( PlayerPositions::id )( i+1 ) ) ); 
   }
   m_pMyStateMachine->setPreviousState( Defending::getInstance() );
   m_pMyStateMachine->setCurrentState( Defending::getInstance() );
   m_pMyStateMachine->changeState( Defending::getInstance() );
}


Teams::~Teams(void)
{
	for( std::vector< FieldPlayers* >::iterator iter = m_playersOnTeam.begin(); iter != m_playersOnTeam.end() ; ++iter  )
	{
		delete *iter;		
	}
	m_playersOnTeam.clear();

	delete  m_pMyStateMachine;
}

void Teams::update()
{
   setClosestPlayerToBall();
   m_pMyStateMachine->update();
   if( !m_hasBall  )
   {
      m_pPlayerReceivingPass = NULL;
   }

   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->update();
   }
   m_pGoalkeeper->update();
   m_hasBall = false;
   for( int i = 0 ; i < 5 ; ++i )
   {
      if( getPlayersOnTeam()[ i ]->isPlayerControllingTheBall() )
      {
         m_hasBall = true;
      }
   }
}

void Teams::draw()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->draw();
   }
   if( m_pPlayerReceivingPass )
   {   
      al_draw_filled_rectangle( m_pPlayerReceivingPass->getPosition().x - 5, m_pPlayerReceivingPass->getPosition().y -5, m_pPlayerReceivingPass->getPosition().x - 15, m_pPlayerReceivingPass->getPosition().y - 15, al_map_rgb( 1.0f, 0.0f, 0.0f ) );
   }
   
   if( doesGoalKeeperHaveBall() )
   {   
      al_draw_filled_rectangle( m_pGoalkeeper->getPosition().x - 5, m_pGoalkeeper->getPosition().y -5, m_pGoalkeeper->getPosition().x - 15, m_pGoalkeeper->getPosition().y - 15, al_map_rgb( 100.0f, 100.0f, 0.0f ) );
   }
   m_pGoalkeeper->draw();
   m_pSupportSpotCalculator->debugDraw();
}

const char* Teams::getTeamName() const
{
	return TEAMS_NAME[ m_myTeam ];
}

void Teams::setPlayerWithBall( Players* pPlayer )
{ 
   if( m_pPlayerWithBall )
   {
      m_pPlayerWithBall->setHasBall( false );
   }
   
   m_pPlayerWithBall = pPlayer;
   m_pPlayerWithBall->setHasBall( true );
}

// TODO: Change the code to remove so much copying. just pass a reference to the vector you want to store the players in.  
std::vector< Players * > Teams::getPlayersOnTeam() const 
{
   std::vector< Players *  > playersOnTeam;
   playersOnTeam.reserve( 5 ); // 4 + 1 goalKeeper
   for( int i = 0 ; i < 4; ++i )
   {
      playersOnTeam.push_back( m_playersOnTeam[ i ] );
   }
   playersOnTeam.push_back( m_pGoalkeeper );
   return playersOnTeam;
}

void Teams::sendPlayersHome()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
   }
   m_pGoalkeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
}

void Teams::sendFieldPlayersHome()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->getStateMachine()->changeState( FieldPlayerReturnHome::getInstance() );
   }
}

void Teams::sendGoalKeeperHome()
{
   m_pGoalkeeper->getStateMachine()->changeState( ReturnGoalkeeperHome::getInstance() );
}

void Teams::changeState( State< Teams >* pToState ) const
{
   m_pMyStateMachine->changeState( pToState );
}

bool Teams::arePlayersHome()
{
   //errored call - MessageDispatcher::getInstance()->dispatchMessage( 0, m_playersOnTeam[ 0 ], m_playersOnTeam[ 1 ], MESSAGE_TYPES::GO_HOME, NULL );
	for( std::vector< FieldPlayers* >::iterator iter = m_playersOnTeam.begin(); iter != m_playersOnTeam.end() ; ++iter )
	{
		if( !(*iter)->isPlayerHome() )
		{
			return false; // returns false is even one of the field player is not home
		}
	}
	if( m_pGoalkeeper->isPlayerHome() )
	{
		return true; // returns true if all fieldPlayers are home and goalKepeer is home.
	}
	return false; // returns false if goalkeeper is not home but the other players are. 
}

bool Teams::doesGoalKeeperHaveBall() const 
{
   return m_pGoalkeeper->isPlayerControllingTheBall();
}

// Checks if the pass is safe to a point, from an opponent. Receiver will be null is we are checking a kick. 
// Changed implementation. Check once again for correctness. 
bool Teams::isPassSafeFromOpponent( glm::vec2 from, glm::vec2 to, const Players* const receiver, Players* const opponent, float force ) const 
{
   // debug , remove. TODO.
   al_draw_line( from.x, from.y, to.x, to.y, al_map_rgb( 1.0f, 255.0f, 0.0f ), 2.0f );
   glm::vec2 toTarget = to - from;
   glm::vec2 toOpponent = opponent->getPosition() - from;
	glm::vec2 toTargetNormalized = glm::normalize( to - from );
   glm::vec2 localPositionOfOpponent = toLocalPos( from, toTargetNormalized, opponent->getPosition() );
   glm::vec2 targetToOpponent = to - opponent->getPosition();
   
   if( localPositionOfOpponent.x < 0 )
   {
      return true;
   }
   // TODO: Check this function, maybe better to check is distance to target is less than distance of target from opponent. 
   if( ( toTarget.x /** toTarget.x + toTarget.y * toTarget.y*/ ) < ( toOpponent.x/* * toOpponent.x + toOpponent.y * toOpponent.y */) )// ( toTarget.x * toTarget.x + toTarget.y * toTarget.y ) > ( opponentToTarget.x * opponentToTarget.x + opponentToTarget.y * opponentToTarget.y )
   {
      if( receiver )
      {
         glm::vec2 receiverToTarget = to - receiver->getPosition();

         if( ( targetToOpponent.x * targetToOpponent.x + targetToOpponent.y * targetToOpponent.y ) > ( receiverToTarget.x * receiverToTarget.x + receiverToTarget.y * receiverToTarget.y ) )
         {
            return true;
         }
         else 
         {
            if( ( targetToOpponent.x * targetToOpponent.x + targetToOpponent.y * targetToOpponent.y ) >( toTarget.x * toTarget.x + toTarget.y * toTarget.y ) )
            {
               return true;
            }
            else
            {
               return false;
            }
         }
      }
      else
      {

         return true;
      }
   }

   float timeForBall = SoccerBall::getSoccerBallInstance()->timeToCoverDistance( glm::vec2( 0.0f, 0.0f ), glm::vec2( localPositionOfOpponent.x, 0.0f ), force );

   float OpponentsReach = opponent->getMaxSpeed() * timeForBall;

   if( fabs( localPositionOfOpponent.y ) < OpponentsReach )
   {
      return false;
   }

	return true;
	// get local position of opponent. 
}

bool Teams::isPassSafeFromAllOpponent( glm::vec2 from, glm::vec2 to, const Players* const receiver, float force ) const 
{
   for( int i = 0 ; i < 5 ; ++i )
   {
      if( !isPassSafeFromOpponent( from, to, receiver, getOpponent()->getPlayersOnTeam()[ i ], force ) )
      {
         return false;
      }
   }
   return true;
}

bool Teams::canShoot( glm::vec2 ballPos, float force, glm::vec2& shotTarget ) const
{
   int numAttempts = 5;
   glm::vec2 opponentGoalCenter = getOpponent()->getGoalPost()->getCenter();
	
   int minY = getOpponent()->getGoalPost()->gettopLeft().y;
   int maxY = getOpponent()->getGoalPost()->getbotRight().y;
	
   glm::vec2 tempShotTarget( opponentGoalCenter.x, minY  );

   while( --numAttempts )
   {
	   int yDisplacement = rand() % ( maxY - minY ) + minY;
       tempShotTarget.y = yDisplacement;
       float time = SoccerBall::getSoccerBallInstance()->timeToCoverDistance( ballPos, tempShotTarget, force );
       if( time > 0.0f )
       {
		   if( isPassSafeFromAllOpponent( ballPos, tempShotTarget, NULL, force ) )
           {
			   shotTarget = tempShotTarget;
			   return true;
           }
       }
	}
	return false;
}

Players* Teams::determineBestSupportingPlayer()
{
   float minDistanceSoFar = 1000000.0f;
   glm::vec2 bestSupportPosition = m_pSupportSpotCalculator->getBestSupportSpot();
   Players* bestSupportPlayer = NULL;
   for( int i = 0 ; i < 5 ; ++i )
   {
      glm::vec2 playerToPosition = getPlayersOnTeam()[ i ]->getPosition() - bestSupportPosition;
      float dist = playerToPosition.x * playerToPosition.x + playerToPosition.y * playerToPosition.y;
      if( dist < minDistanceSoFar )
      {
         bestSupportPlayer = getPlayersOnTeam()[ i ];
         minDistanceSoFar = dist;
      }
   }
   return bestSupportPlayer;
}

bool Teams::findPass( const Players* const passer, Players*& receiver, glm::vec2& passTarget, float force, float minPassingDistance ) const
{
   std::vector< Players* > myPlayers = getPlayersOnTeam();
   std::vector< Players* >::const_iterator currentPlayer = myPlayers.begin();
	float closestToBall = 10000.0f;// random large value. 
	glm::vec2 ballTarget;
	for( currentPlayer ; currentPlayer != myPlayers.end(); ++currentPlayer )
	{
      std::cout<<" Checking layers ";
		glm::vec2 toReceiver = passer->getPosition() - ( *currentPlayer )->getPosition();
		if( *currentPlayer != passer && ( toReceiver.x * toReceiver.x + toReceiver.y * toReceiver.y ) > ( minPassingDistance * minPassingDistance ) )
		{
			if( getBestPassToReceiver( passer, *currentPlayer, ballTarget, force ) )
			{
				float toGoalHorizontal = fabs( ballTarget.x - getOpponent()->getGoalPost()->getCenter().x );
				if( toGoalHorizontal < closestToBall )
				{
					closestToBall = toGoalHorizontal;
					receiver = *currentPlayer;

					passTarget = ballTarget;
				}
			}
		}
	}

	if( receiver )
	{
		return true;
	}
	return false;
}

bool Teams::getBestPassToReceiver( const Players* const passer, const Players* const receiver, glm::vec2& passTarget, float force ) const
{
	float timeForBall = SoccerBall::getSoccerBallInstance()->timeToCoverDistance( SoccerBall::getSoccerBallInstance()->getPosition(), receiver->getPosition(), force );
	if( time <= 0 )
	{
		return false;
	}
	
	float interceptRange = timeForBall * receiver->getMaxSpeed() * 0.3f; // TODO: Magic number 0.3f , make it const. 

	glm::vec2 positionTop( receiver->getPosition().x, receiver->getPosition().y - interceptRange );
	if( positionTop.y < 20.0f )  // height of top walls is 20 pixels
	{ 
		positionTop.y = 20.0f;
	}
	
	glm::vec2 positionBot( receiver->getPosition().x, receiver->getPosition().y + interceptRange );
	if( positionBot.y > 620.0f )
	{
		positionBot.y = 620;
	}

	glm::vec2 positionsToCheck[ 3 ] = { positionTop, receiver->getPosition(), positionBot };

	float closest = 10000000.0f;
	bool result = false;

	for( int i = 0 ; i < 3 ; ++i )
	{
		glm::vec2 toPoint = positionsToCheck[ i ] - getOpponent()->getGoalPost()->getCenter();
		float distance = sqrtf( toPoint.x * toPoint.x + toPoint.y * toPoint.y ); 
		if( distance < closest && isPassSafeFromAllOpponent( SoccerBall::getSoccerBallInstance()->getPosition(), positionsToCheck[ i ], receiver, force ) )
		{
			closest = distance;
			passTarget = positionsToCheck[ i ];
			result = true;
		}
	}

	return result;
}

void Teams::setClosestPlayerToBall()
{ 
   // TODO: Refactor the system to calculate which player is closest to the ball
   float closest = 10000000.0f;
   glm::vec2 ballPosition = SoccerBall::getSoccerBallInstance()->getPosition();
   for( int i = 0 ; i < 5 ; ++i )
   {
      glm::vec2 toBall = ballPosition - getPlayersOnTeam()[ i ]->getPosition();
      float distToBall = toBall.x * toBall.x + toBall.y * toBall.y;
      if( distToBall < closest )
      {
         m_pPlayerClosestToBall = getPlayersOnTeam()[ i ];
         closest = distToBall;
      }
      
      getPlayersOnTeam()[ i ]->setIsClosestToBall( false );
   }
   m_pPlayerClosestToBall->setIsClosestToBall( true );
}

void Teams::requestPass( Players* pPlayerRequesting )
{
   if( isPassSafeFromAllOpponent( m_pPlayerWithBall->getPosition(), pPlayerRequesting->getPosition(), pPlayerRequesting, 40.0f ) ) // TODO: Magic Number
   {
      MessageDispatcher::getInstance()->dispatchMessage( 0.0f, pPlayerRequesting, m_pPlayerWithBall, MESSAGE_TYPES::PASS_TO_ME, NULL );
   }
}

glm::vec2 Teams::getBestSupportSpot()
{
   return m_pSupportSpotCalculator->getBestSupportSpot();
}