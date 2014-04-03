// This class defines the structure for a message. 
#pragma once
#include<math.h>
#include<iostream>

class BaseGameEntity;
static const double SMALLEST_POSSIBLE_DELAY = 0.25;

struct MESSAGE_TYPES
{
   enum msg
   {
      RECEIVE_BALL,
      SUPPORT_ATTACKER,
      GO_HOME,
      WAIT,
      PASS_TO_ME,
      NUM_MESSAGES
   };
};

static const char* MESSAGE_TO_STRING[ MESSAGE_TYPES::NUM_MESSAGES ] = 
{
   "RECEIVE_BALL",
   "SUPPORT_ATTACKER",
   "GO_HOME",
   "WAIT",
   "PASS_TO_ME",
};

class Message
{
public:
   Message( double time, BaseGameEntity* sender, BaseGameEntity* receiver, MESSAGE_TYPES::msg messageType, void* extraInfo = NULL );

   BaseGameEntity* getSender() const { return m_pSender; }
   BaseGameEntity* getReceiver() const { return m_pReceiver; }
   MESSAGE_TYPES::msg getMessageType() const { return m_messageType; }
   double getDispatchTime() const { return m_dispatchTime; }
   void setDispatchTime( double dispatchTime ){ m_dispatchTime = dispatchTime; }
   void* getExtraInfo() const { return m_extraInfo; }

private:
   BaseGameEntity* m_pSender;
   BaseGameEntity* m_pReceiver;
   MESSAGE_TYPES::msg m_messageType;
   double m_dispatchTime;
   void* m_extraInfo;

};

inline bool operator==( const Message& t1, const Message& t2 )
{
   return ( fabs( t1.getDispatchTime() - t2.getDispatchTime() ) < SMALLEST_POSSIBLE_DELAY ) &&
          ( t1.getSender() == t2.getSender() )        &&
          ( t1.getReceiver() == t2.getReceiver() )    &&
          ( t1.getMessageType() == t2.getMessageType() );
}

inline bool operator<(const Message& t1, const Message& t2)
{
  if ( t1 == t2 )
  {
    return false;
  }
  else
  {
    return  ( t1.getDispatchTime() < t2.getDispatchTime() );
  }
}

template <class T>
inline T DereferenceToType(void* p)
{
  return *( static_cast< T* >(p) );
}
