#include "FieldPlayersState.h"
#include "FieldPlayers.h"
#include "SteeringBehaviors.h"
#include "SoccerBall.h"
#include <iostream>

// Wait State functions
void Wait::enter( Players* pPlayer )
{
}

void Wait::execute( Players* pPlayer )
{
}

void Wait::exit( Players* pPlayer )
{
}

Wait* Wait::getInstance()
{
   static Wait waitState;
   return &waitState;
}

//*****************************************************************
// ChaseBall State functions

void ChaseBall::enter( Players* pPlayer )
{
	pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
	pPlayer->getSteeringBehavior()->seekOn();
}

void ChaseBall::execute( Players* pPlayer )
{
	if( pPlayer->isInKickingRangeOfTheBall() )
	{
		pPlayer->getStateMachine()->changeState( KickBall::getInstance() );
		return;
	}

	if( pPlayer->isPlayerClosestToBall() )
	{
		pPlayer->getSteeringBehavior()->setTarget( SoccerBall::getSoccerBallInstance() );
		return;
	}

	pPlayer->getStateMachine()->changeState( ReturnHome::getInstance() );
}

void ChaseBall::exit( Players* pPlayer )
{
	pPlayer->getSteeringBehavior()->seekOff();
}

ChaseBall* ChaseBall::getInstance()
{
   static ChaseBall chaseBallState;
   return &chaseBallState;
}

//*****************************************************************
// ReceiveBall State functions

void ReceiveBall::enter( Players* pPlayer )
{
}

void ReceiveBall::execute( Players* pPlayer )
{
}

void ReceiveBall::exit( Players* pPlayer )
{
}

ReceiveBall* ReceiveBall::getInstance()
{
   static ReceiveBall receiveBallState;
   return &receiveBallState;
}

//*****************************************************************
// Dribble State functions

void Dribble::enter( Players* pPlayer )
{
}

void Dribble::execute( Players* pPlayer )
{
}

void Dribble::exit( Players* pPlayer )
{
}

Dribble* Dribble::getInstance()
{
   static Dribble dribbleState;
   return &dribbleState;
}

//*****************************************************************
// KickBall State functions

void KickBall::enter( Players* pPlayer )
{
}

void KickBall::execute( Players* pPlayer )
{
}

void KickBall::exit( Players* pPlayer )
{
}

KickBall* KickBall::getInstance()
{
   static KickBall kickBallState;
   return &kickBallState;
}

//*****************************************************************
// SupportPlayerWithBall State functions

void SupportPlayerWithBall::enter( Players* pPlayer )
{
}

void SupportPlayerWithBall::execute( Players* pPlayer )
{
}

void SupportPlayerWithBall::exit( Players* pPlayer )
{
}

SupportPlayerWithBall* SupportPlayerWithBall::getInstance()
{
   static SupportPlayerWithBall supportPlayerState;
   return &supportPlayerState;
}

//*****************************************************************
// ReturnHome State functions

void ReturnHome::enter( Players* pPlayer )
{
}

void ReturnHome::execute( Players* pPlayer )
{
}

void ReturnHome::exit( Players* pPlayer )
{
}

ReturnHome* ReturnHome::getInstance()
{
   static ReturnHome returnHomeState;
   return &returnHomeState;
}