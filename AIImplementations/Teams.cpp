#include "Teams.h"
#include "GoalKeeper.h"
#include "Players.h"
#include "FieldPlayers.h"
#include "StateMachine.h"
#include "TeamStates.h"
#include <iostream>
#include "Teams.h"
#include "SteeringBehaviors.h"

static const char* TEAMS_NAME[2] = 
{
	"Blue",
	"Red"
};
static const int TOTAL_PLAYERS = 4;

Teams::Teams( TEAM::id myTeam )
   : m_myTeam( myTeam )
   , m_playersOnTeam()
   , m_pGoalkeeper( new GoalKeeper( this ) )
   , m_pPlayerWithBall( NULL )
   , m_pSupportingPlayer( NULL )
   , m_pPlayerClosestToBall( NULL )
   , m_pPlayerReceivingPass( NULL )
   , m_pOpponent( NULL )
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
   m_pMyStateMachine->setGlobalState( NULL );
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
   m_pMyStateMachine->update();
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->update();
   }
   m_pGoalkeeper->update();
}

void Teams::draw()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      m_playersOnTeam[ i ]->draw();
   }
   m_pGoalkeeper->draw();
}

const char* Teams::getTeamName()
{
	return TEAMS_NAME[ m_myTeam ];
}

void Teams::sendPlayersHome()
{
   for( int i = 0  ; i < TOTAL_PLAYERS ; ++i )
   {
      // set player to go home m_playersOnTeam[ i ]->goHome();
   }
}

void Teams::changeState( State< Teams >* pToState ) const
{
   m_pMyStateMachine->changeState( pToState );
}

bool Teams::arePlayersHome()
{
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