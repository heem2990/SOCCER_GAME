#include "MessageDispatcher.h"
#include "BaseGameEntity.h"

void MessageDispatcher::dischargeMessage( BaseGameEntity* pReceiver, const Message& msg )
{
   if( !pReceiver->handleMessage( msg ) )
   {
      // TODO: Code for when a message is not handled properly. FOR Debug purposes
   }
}

void MessageDispatcher::dispatchMessage( double delay, BaseGameEntity* sender, BaseGameEntity* receive, MESSAGE_TYPES::msg messageToSend, void* extraInfo )
{
   Message messagePacket( delay, sender , receive , messageToSend, extraInfo );
   if( delay <= 0.0 )
   {
      dischargeMessage( receive , messagePacket );
   }
   else
   {
      double currentTime = GetCurrentTime();
      messagePacket.setDispatchTime( currentTime + messagePacket.getDispatchTime() );
      m_priorityQueue.insert( messagePacket );
   }
}

void MessageDispatcher::dispatchDelayedMessages()
{
   double currentTime = GetCurrentTime();

   while( ( m_priorityQueue.begin()->getDispatchTime() < currentTime ) && ( m_priorityQueue.begin()->getDispatchTime() > 0 ) )
   {
      Message messageToSend = *( m_priorityQueue.begin() );
      dischargeMessage( messageToSend.getReceiver(), messageToSend );

      m_priorityQueue.erase( m_priorityQueue.begin() );
   }
}