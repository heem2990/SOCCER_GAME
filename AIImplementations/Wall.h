#pragma once
#include "MyRect.h"
class Wall :
   public MyRect
{
public:
   Wall( glm::vec2 topLeft, glm::vec2 botRight , glm::vec2 normal );
   ~Wall(void);

   glm::vec2 reflectAgainstNormal( glm::vec2 vectorToReflect );

private:
   glm::vec2 m_normalToWall;
};

