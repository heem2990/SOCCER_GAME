#include "TeamStates.h"
#include "Teams.h"
#include <iostream>

//*****************************************************************
// Attacking state
void Attacking::enter( Teams* pTeam )
{
	std::cout<<"Team "<<pTeam->getTeamName()<<" Entered attacking State"<<std::endl;
}

void Attacking::execute( Teams* pTeam )
{
	//std::cout<<"******Team "<<pTeam->getTeamName()<<" is attacking"<<std::endl;
	//if( !pTeam->hasControl() )
	//{
	//	pTeam->changeState( Defending::getInstance() );
	//}
	//Supporting player code
}

void Attacking::exit( Teams* pTeam )
{
	std::cout<<"***********Team "<<pTeam->getTeamName()<<" has exited attacking state"<<std::endl;
}

Attacking* Attacking::getInstance()
{
	static Attacking attackingStateInstance;
	return &attackingStateInstance;
}

//*****************************************************************
// Defending state
void Defending::enter( Teams* pTeam )
{
	std::cout<<"Team "<<pTeam->getTeamName()<<" Entered Defending State"<<std::endl;
	//pTeam->sendPlayersHome();
}

void Defending::execute( Teams* pTeam )
{
	//std::cout<<"******Team "<<pTeam->getTeamName()<<" is defending"<<std::endl;
	/*if( pTeam->hasControl() )
	{
		pTeam->changeState( Attacking::getInstance() );
	}*/
	//if( team )
}

void Defending::exit( Teams* pTeam )
{
	std::cout<<"***********Team "<<pTeam->getTeamName()<<" has exited defending state"<<std::endl;
}

Defending* Defending::getInstance()
{
	static Defending defendingStateInstance;
	return &defendingStateInstance;
}

//*****************************************************************
// Prepare for kick off state
void KickOff::enter( Teams* pTeam )
{
	std::cout<<"******Team "<<pTeam->getTeamName()<<" has entered KickOff"<<std::endl;
	pTeam->setClosestPlayerToBall();
	//pTeam->setPlayerWithBall( NULL );
	pTeam->setReceivingPlayer( NULL );
	pTeam->setSupportingPlayer( NULL );

	pTeam->sendPlayersHome();
}

void KickOff::execute( Teams* pTeam )
{
	//if( pTeam->arePlayersHome() && pTeam->getOpponent()->arePlayersHome() )
	//{
	//	pTeam->changeState( Defending::getInstance() );
	//}
}

void KickOff::exit( Teams* pTeam )
{
	std::cout<<"******Team "<<pTeam->getTeamName()<<" has exited KickOff"<<std::endl;
}

KickOff* KickOff::getInstance()
{
	static KickOff kickOffStateInstance;
	return &kickOffStateInstance;
}