#include "ShapeFactory.h"

 void ShapeFactory::drawTriangle(Color color, std::list<Coordinate>& coordinates){
   glColor3f (color.getRed(),color.getGreen(),color.getBlue());
   glBegin(GL_TRIANGLES);
      for(Coordinate c : coordinates){
        glVertex3f (c.getX(), c.getY(), c.getZ());
      }
   glEnd();
}
