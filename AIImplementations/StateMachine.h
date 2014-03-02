#pragma once
#include"State.h"

template<class entityType>
class StateMachine
{
public:
   StateMachine( entityType* pOwner )
      : m_pOwner( pOwner )
      , m_pCurrentState( 0 )
      , m_pGlobalState( 0 )
      , m_pPreviousState( 0 )
   {
   }
   
   void setGlobalState( State< entityType >* pState ){ m_pGlobalState = pState; }
   void setCurrentState( State< entityType >* pState ){ m_pCurrentState = pState; }
   void setPreviousState( State< entityType >* pState ){ m_pPreviousState = pState; }

   State< entityType >* getCurrentState() const { return m_pCurrentState; }
   State< entityType >* getGlobalState() const { return m_pGlobalState; }
   State< entityType >* getPreviousState() const { return m_pPreviousState; }

   void update() const 
   {
      if( m_pGlobalState )
      {
         m_pGlobalState->execute( m_pOwner );
      }
      if( m_pCurrentState )
      {
         m_pCurrentState->execute( m_pOwner );
      }

   }

   void changeState( const State< entityType* > pState )
   {
      if( pState )
      {
         m_pPreviousState = m_pCurrentState;
         m_pCurrentState->exit( m_pOwner );
         m_pCurrentState = pState;
         m_pCurrentState->enter( m_pOwner );
      }

   }

   void revertToPreviousState() const
   {
      changeState( m_pPreviousState );

   }
   bool isInState( const State< entityType >& rState ) const
   {
      if( m_pCurrentState == rState )
      {
         return true;
      }
      return false;
   }

private:
   entityType* m_pOwner;
   State< entityType >* m_pCurrentState;
   State< entityType >* m_pPreviousState;
   State< entityType >* m_pGlobalState;

};

