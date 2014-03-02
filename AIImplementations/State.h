#pragma once

template< class entityType >
class State
{
public:
   State(void){};

   virtual void enter( entityType* pEntity ) = 0;
   virtual void execute( entityType* pEntity ) = 0;
   virtual void exit( entityType* pEntity ) = 0;
   virtual const char* getStateName() const { return "State"; }
};

