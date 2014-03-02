#include "FieldPlayersState.h"

// Wait State functions
void Wait::enter( FieldPlayers* pPlayer )
{
}

void Wait::execute( FieldPlayers* pPlayer )
{
}

void Wait::exit( FieldPlayers* pPlayer )
{
}

Wait* Wait::getInstance()
{
   static Wait waitState;
   return &waitState;
}

//*****************************************************************
// ChaseBall State functions

void ChaseBall::enter( FieldPlayers* pPlayer )
{
}

void ChaseBall::execute( FieldPlayers* pPlayer )
{
}

void ChaseBall::exit( FieldPlayers* pPlayer )
{
}

ChaseBall* ChaseBall::getInstance()
{
   static ChaseBall chaseBallState;
   return &chaseBallState;
}

//*****************************************************************
// ReceiveBall State functions

void ReceiveBall::enter( FieldPlayers* pPlayer )
{
}

void ReceiveBall::execute( FieldPlayers* pPlayer )
{
}

void ReceiveBall::exit( FieldPlayers* pPlayer )
{
}

ReceiveBall* ReceiveBall::getInstance()
{
   static ReceiveBall receiveBallState;
   return &receiveBallState;
}

//*****************************************************************
// Dribble State functions

void Dribble::enter( FieldPlayers* pPlayer )
{
}

void Dribble::execute( FieldPlayers* pPlayer )
{
}

void Dribble::exit( FieldPlayers* pPlayer )
{
}

Dribble* Dribble::getInstance()
{
   static Dribble dribbleState;
   return &dribbleState;
}

//*****************************************************************
// KickBall State functions

void KickBall::enter( FieldPlayers* pPlayer )
{
}

void KickBall::execute( FieldPlayers* pPlayer )
{
}

void KickBall::exit( FieldPlayers* pPlayer )
{
}

KickBall* KickBall::getInstance()
{
   static KickBall kickBallState;
   return &kickBallState;
}

//*****************************************************************
// SupportPlayerWithBall State functions

void SupportPlayerWithBall::enter( FieldPlayers* pPlayer )
{
}

void SupportPlayerWithBall::execute( FieldPlayers* pPlayer )
{
}

void SupportPlayerWithBall::exit( FieldPlayers* pPlayer )
{
}

SupportPlayerWithBall* SupportPlayerWithBall::getInstance()
{
   static SupportPlayerWithBall supportPlayerState;
   return &supportPlayerState;
}