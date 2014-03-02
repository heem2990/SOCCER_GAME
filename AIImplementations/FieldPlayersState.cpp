#include "FieldPlayersState.h"

// Wait State functions
void Wait::enter( FieldPlayers* )
{
}

void Wait::execute( FieldPlayers* )
{
}

void Wait::exit( FieldPlayers* )
{
}

Wait* Wait::getInstance()
{
   static Wait waitState;
   return &waitState;
}

// ChaseBall State functions
void ChaseBall::enter( FieldPlayers* )
{
}

void ChaseBall::execute( FieldPlayers* )
{
}

void ChaseBall::exit( FieldPlayers* )
{
}

ChaseBall* ChaseBall::getInstance()
{
   static ChaseBall chaseBallState;
   return &chaseBallState;
}

// ReceiveBall State functions
void ReceiveBall::enter( FieldPlayers* )
{
}

void ReceiveBall::execute( FieldPlayers* )
{
}

void ReceiveBall::exit( FieldPlayers* )
{
}

ReceiveBall* ReceiveBall::getInstance()
{
   static ReceiveBall receiveBallState;
   return &receiveBallState;
}

// Dribble State functions
void Dribble::enter( FieldPlayers* )
{
}

void Dribble::execute( FieldPlayers* )
{
}

void Dribble::exit( FieldPlayers* )
{
}

Dribble* Dribble::getInstance()
{
   static Dribble dribbleState;
   return &dribbleState;
}

// KickBall State functions
void KickBall::enter( FieldPlayers* )
{
}

void KickBall::execute( FieldPlayers* )
{
}

void KickBall::exit( FieldPlayers* )
{
}

KickBall* KickBall::getInstance()
{
   static KickBall kickBallState;
   return &kickBallState;
}

// SupportPlayerWithBall State functions
void SupportPlayerWithBall::enter( FieldPlayers* )
{
}

void SupportPlayerWithBall::execute( FieldPlayers* )
{
}

void SupportPlayerWithBall::exit( FieldPlayers* )
{
}

SupportPlayerWithBall* SupportPlayerWithBall::getInstance()
{
   static SupportPlayerWithBall supportPlayerState;
   return &supportPlayerState;
}