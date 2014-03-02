#include "Teams.h"
#include "GoalKeeper.h"
#include "Players.h"
#include "FieldPlayers.h"

Teams::Teams( TEAM::id myTeam )
   : m_myTeam( myTeam )
   , m_playersOnTeam()
   , m_pGoalkeeper( new GoalKeeper( m_myTeam ) )
{
   for( int i = 0 ; i < 4 ; ++i )
   {
      m_playersOnTeam.push_back( new FieldPlayers( m_myTeam, ( PlayerPositions::id )( i+1 ) ) ); 
   }
}


Teams::~Teams(void)
{
}

void Teams::update()
{
   for( int i = 0  ; i < 4 ; ++i )
   {
      m_playersOnTeam[ i ]->update();
   }
   m_pGoalkeeper->update();
   draw();
}

void Teams::draw()
{
   for( int i = 0  ; i < 4 ; ++i )
   {
      m_playersOnTeam[ i ]->draw();
   }
   m_pGoalkeeper->draw();
}