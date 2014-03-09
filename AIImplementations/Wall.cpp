#include "Wall.h"
#include <iostream>

Wall::Wall( glm::vec2 topLeft, glm::vec2 botRight , glm::vec2 normal )
   : MyRect( topLeft, botRight )
   , m_normalToWall( normal )
{

}


Wall::~Wall(void)
{
}

glm::vec2 Wall::reflectAgainstNormal( glm::vec2 vectorToReflect )
{
   glm::vec2 vectorInDirectionOfNormal = glm::dot( vectorToReflect, glm::normalize( m_normalToWall ) ) * glm::normalize( m_normalToWall );
   glm::vec2 vectorNormalToNormal = vectorToReflect - vectorInDirectionOfNormal;
   glm::vec2 reflectedVelocity = vectorNormalToNormal - vectorInDirectionOfNormal;
   return ( reflectedVelocity );
}