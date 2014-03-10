#pragma once
#include"State.h"

template<class entityType>
class StateMachine
{
public:
   StateMachine( entityType* pOwner )
      : m_pOwner( pOwner )
      , m_pCurrentState( NULL )
      , m_pPreviousState( NULL )
   {
   }
   
   void setCurrentState( State< entityType >* pState ){ m_pCurrentState = pState; }
   void setPreviousState( State< entityType >* pState ){ m_pPreviousState = pState; }

   State< entityType >* getCurrentState() const { return m_pCurrentState; }
   State< entityType >* getPreviousState() const { return m_pPreviousState; }

   void update() const 
   {
      if( m_pCurrentState )
      {
         m_pCurrentState->execute( m_pOwner );
      }

   }

   void changeState( State< entityType >* pState )
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
};

