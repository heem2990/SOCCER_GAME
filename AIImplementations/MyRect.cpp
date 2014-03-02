#include "MyRect.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>

MyRect::MyRect( glm::vec2 topLeft, glm::vec2 botRight )
   : m_topLeft( topLeft )
   , m_Botright( botRight )
{
}

bool MyRect::contains( const glm::vec2 point ) const 
{ 
   if( ( point.x <= m_Botright.x && point.x >= m_topLeft.x ) && ( point.y <= m_Botright.y && point.y >= m_topLeft.y ) )
   {
      return true;
   }
   return false;
}

void MyRect::debugDraw()
{
   al_draw_line( m_topLeft.x , m_topLeft.y , m_Botright.x, m_topLeft.y, al_map_rgb( 1,1,1 ) , 3.0f );
   al_draw_line( m_topLeft.x , m_topLeft.y , m_topLeft.x, m_Botright.y, al_map_rgb( 1,1,1 ) , 3.0f );
   al_draw_line( m_Botright.x , m_Botright.y , m_Botright.x, m_topLeft.y, al_map_rgb( 1,1,1 ) , 3.0f );
   al_draw_line( m_Botright.x , m_Botright.y , m_topLeft.x, m_Botright.y, al_map_rgb( 1,1,1 ) , 3.0f );
}