#include "SupportSpotCalculator.h"
#include "SoccerGame.h"
#include "Teams.h"
#include "MyRect.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>

SupportSpotCalculator::SupportSpotCalculator( Teams* myteam )
	: m_supportSpots()
	, m_myTeam( myteam )
{
	m_supportSpots.reserve( 36 );
	int start = myteam->getTeamColor() == TEAM::BLUE? 9 : 0;
	int end = myteam->getTeamColor() == TEAM::BLUE? 18: 9;
	for(  int i = start; i < end ; ++i )
	{
		MyRect currentRegion = *( SoccerGame::getRegions()[ i ] );
		glm::vec2 innerTopLeft ( ( currentRegion.getCenter().x + currentRegion.gettopLeft().x )/ 2,
			                     ( currentRegion.getCenter().y + currentRegion.gettopLeft().y )/ 2 );
		
		glm::vec2 innerTopRight( ( currentRegion.getCenter().x + currentRegion.getbotRight().x )/ 2,
			                     ( currentRegion.getCenter().y + currentRegion.gettopLeft().y )/ 2 );
		
		glm::vec2 innerBotLeft ( ( currentRegion.getCenter().x + currentRegion.gettopLeft().x )/ 2,
			                     ( currentRegion.getCenter().y + currentRegion.getbotRight().y )/ 2 );
		
		glm::vec2 innerBotRight( ( currentRegion.getCenter().x + currentRegion.getbotRight().x )/ 2,
			                     ( currentRegion.getCenter().y + currentRegion.getbotRight().y )/ 2 );

		m_supportSpots.push_back( SupportSpot( innerTopLeft, 1 ) );
		m_supportSpots.push_back( SupportSpot( innerTopRight, 1 ) );
		m_supportSpots.push_back( SupportSpot( innerBotLeft, 1 ) );
		m_supportSpots.push_back( SupportSpot( innerBotRight, 1 ) );
	}
}


SupportSpotCalculator::~SupportSpotCalculator(void)
{
}

void SupportSpotCalculator::debugDraw()
{
	for( int i = 0 ; i < 36 ; ++i )
	{
		al_draw_circle( m_supportSpots[ i ].m_supportSpot.x, m_supportSpots[ i ].m_supportSpot.y, m_supportSpots[ i ].m_rating *3.0f, al_map_rgb( 0.0f, 0.0f, 0.0f ), 2.0f );
	}
}

glm::vec2 SupportSpotCalculator::getBestSupportSpot()
{
	glm::vec2 bestSupportSpot = glm::vec2( 0, 0 );
	int maxScore = 0;
	for( int i = 0 ; i < 36 ; ++i )
	{
		m_supportSpots[ i ].m_rating = 1;
		// if pass to spot is safe from all opponents add 3
		// if goal can be scored from this position add 2
		// add rating based on how far the point is. 
		// check if this is the current highest score, in which case set the bestSupportSpot as this point. 
	}

	return glm::vec2();
}
