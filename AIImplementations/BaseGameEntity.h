// Interface class for most game entities to inherit from.
#pragma once

#include <allegro5\allegro.h>
#include "glm\vec2.hpp"

class Message;

class BaseGameEntity
{
public:
	BaseGameEntity( const char* imageName, glm::vec2 position );

	virtual void draw() = 0;
   virtual void update() = 0;
   virtual bool handleMessage( const Message& msg ) = 0;

	int getId() const { return m_id; }
   ALLEGRO_BITMAP* getImage() const { return m_sprite; }
   glm::vec2 getPosition() const { return m_position; }
   void setPosition( glm::vec2 position ){ m_position = position; }
   // something for bounds. 

private:
   static int ms_iStaticID ;
	int m_id;
   glm::vec2 m_position;
   ALLEGRO_BITMAP* m_sprite;

};

