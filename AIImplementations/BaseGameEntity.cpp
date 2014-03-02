#include "BaseGameEntity.h"
#include<iostream>
#include<math.h>

int BaseGameEntity::ms_iStaticID = 0;
BaseGameEntity::BaseGameEntity( const char* imageName , glm::vec2 position )
   : m_id( ++ms_iStaticID )
   , m_position( position )
   , m_sprite( al_load_bitmap( imageName ) )
{
	if( !m_sprite )
	{
		std::cout<<"ERROR: NO SPRITE FOUND "<<imageName<<std::endl;
	}
}

void BaseGameEntity::draw()
{
   al_draw_bitmap( m_sprite, m_position.x, m_position.y, NULL );
}
