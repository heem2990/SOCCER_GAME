#pragma once

#include <allegro5\allegro.h>
#include "glm\vec2.hpp"

typedef unsigned int u32;
typedef signed int s32;

class BaseGameEntity
{
public:
	BaseGameEntity( const char* imageName, glm::vec2 position );

	virtual void draw() ;
   virtual void update() = 0;

	int getId() const { return m_id; }
   ALLEGRO_BITMAP* getImage()  { return m_sprite; }
   glm::vec2 getPosition(){ return m_position; }
   void setPosition( glm::vec2 position ){ m_position = position; }
   // something for bounds. 

private:
   static int ms_iStaticID;
	int m_id;
   glm::vec2 m_position;
   ALLEGRO_BITMAP* m_sprite;

};

