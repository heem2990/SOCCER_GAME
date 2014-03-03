#include "Message.h"

Message::Message( double time, BaseGameEntity* sender, BaseGameEntity* receiver, MESSAGE_TYPES::msg messageType, void* extraInfo )
   : m_pSender( sender )
   , m_pReceiver( receiver )
   , m_messageType( messageType )
   , m_dispatchTime( time )
   , m_extraInfo( extraInfo )
{
}
