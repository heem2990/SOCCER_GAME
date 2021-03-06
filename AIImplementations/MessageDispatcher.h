// Singleton class to handle message passing between the players. 
#pragma once
#include <set>
#include "Message.h"

class MessageDispatcher
{
public:
   
   void dispatchMessage( double delay, BaseGameEntity* sender, BaseGameEntity* receive, MESSAGE_TYPES::msg messageToSend, void* extraInfo );
   void dispatchDelayedMessages();

   static MessageDispatcher* getInstance();

private:
   std::set<Message> m_priorityQueue;

   void dischargeMessage( BaseGameEntity* pReceiver, const Message& msg );
   MessageDispatcher(void){}
};

