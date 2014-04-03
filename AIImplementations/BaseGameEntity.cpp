#include "BaseGameEntity.h"
#include<iostream>
#include<math.h>

int BaseGameEntity::ms_iStaticID = 0; //This is used to maintain a unique ID for each entity in the game.  
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
