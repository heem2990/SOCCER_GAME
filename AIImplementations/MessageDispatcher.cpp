#include "MessageDispatcher.h"
#include "BaseGameEntity.h"

// This is the function that basically calls handleMessage in the receiver. 
void MessageDispatcher::dischargeMessage( BaseGameEntity* pReceiver, const Message& msg )
{
   if( !pReceiver->handleMessage( msg ) )
   {
      // TODO: Code for when a message is not handled properly. FOR Debug purposes
   }
}

// Discharges the message, else adds it to queue.
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
      messagePacket.setDispatchTime( currentTime + ( messagePacket.getDispatchTime() * 1000 ) );
      m_priorityQueue.insert( messagePacket );
   }
}

// Function to see through the messages in priority queue, and see if there are any delayed messages waiting to be sent.
void MessageDispatcher::dispatchDelayedMessages()
{
   if( m_priorityQueue.size() == 0 )
   {
      return;
   }
   double currentTime = GetCurrentTime();

   while( ( m_priorityQueue.begin()->getDispatchTime() < currentTime ) && ( m_priorityQueue.begin()->getDispatchTime() > 0 ) )
   {
      Message messageToSend = *( m_priorityQueue.begin() );
      dischargeMessage( messageToSend.getReceiver(), messageToSend );

      m_priorityQueue.erase( m_priorityQueue.begin() );
   }
}

MessageDispatcher* MessageDispatcher::getInstance()
{
   static MessageDispatcher messageDispatcher;
   return &messageDispatcher;
}