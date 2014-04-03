// This class determines the different support spots a supporting player can go to, to ask for a pass. 
// It calculates the weight of each spot based on parameters such as how easy it is to pass, if a goal can be scored etc. 
#pragma once
#include "glm\vec2.hpp"
#include <vector>

class Teams;

struct SupportSpot
{
	glm::vec2 m_supportSpot;
	int m_rating;

	SupportSpot( glm::vec2 supportSpot, int rating )
		: m_supportSpot( supportSpot )
		, m_rating( rating )
	{
	}
};

class SupportSpotCalculator
{
public:
	SupportSpotCalculator( Teams* myTeam );
	~SupportSpotCalculator(void);

	glm::vec2 getBestSupportSpot();
	void debugDraw();

private:
	std::vector< SupportSpot > m_supportSpots;	
	Teams* m_pMyTeam;
};

