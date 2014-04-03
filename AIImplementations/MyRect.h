// Base class to denote a rectangular region. 
#pragma once
#include<glm\glm.hpp>
class MyRect
{
public:
   MyRect( glm::vec2 topLeft, glm::vec2 botRight );

   glm::vec2 gettopLeft() const { return m_topLeft; }
   glm::vec2 getbotRight() const { return m_Botright; }
   glm::vec2 getCenter() const { return glm::vec2( ( m_topLeft.x + m_Botright.x )/2 , ( m_topLeft.y + m_Botright.y )/2 );}
   bool contains( const glm::vec2 point ) const ;
   void debugDraw();

private:
   glm::vec2 m_topLeft;
   glm::vec2 m_Botright;
};

