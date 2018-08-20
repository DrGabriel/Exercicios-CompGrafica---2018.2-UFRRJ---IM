#include "ShapeFactory.h"

 void ShapeFactory::drawTriangle(std::vector<Color> colors, std::vector<Coordinate>& coordinates, bool fillShape){

    if(fillShape){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
   glBegin(GL_TRIANGLES);
      for(unsigned i = 0; (i < coordinates.size()); i++){
        glColor3f (colors[i].getRed(),colors[i].getGreen(),colors[i].getBlue());
        glVertex3f (coordinates[i].getX(), coordinates[i].getY(), coordinates[i].getZ());
      }
   glEnd();
   glFlush();
}
void ShapeFactory::drawPoint(Color color, Coordinate& coordinate){
    glBegin(GL_POINTS);
        glColor3f (color.getRed(),color.getGreen(),color.getBlue());
        glVertex3f (coordinate.getX(), coordinate.getY(), coordinate.getZ());
    glEnd();
    glFlush();
}
void ShapeFactory::drawLine(std::vector<Color> colors, std::vector<Coordinate>& coordinates){
    glBegin(GL_LINES);
        glColor3f (colors[0].getRed(),colors[0].getGreen(),colors[0].getBlue());
        glVertex3f (coordinates[0].getX(), coordinates[0].getY(), coordinates[0].getZ());

        glColor3f (colors[1].getRed(),colors[1].getGreen(),colors[1].getBlue());
        glVertex3f (coordinates[1].getX(), coordinates[1].getY(), coordinates[1].getZ());
    glEnd();
    glFlush();
}
void ShapeFactory::drawXYAxis(std::vector<Color> colors){
    Coordinate co1(0.5, 0.0, 0.0),co2(0.5, 1.0, 0.0), co3(0.0, 0.5, 0.0), co4(1.0, 0.5, 0.0);

    std::vector<Color> axisXColor = {colors[0], colors[1]};
    std::vector<Coordinate> axisXCoordinates = {co1,co2};

    std::vector<Color> axisYColor = {colors[2], colors[3]};
    std::vector<Coordinate> axisYCoordinates = {co3,co4};

    ShapeFactory::drawLine(axisXColor,axisXCoordinates);
    ShapeFactory::drawLine(axisYColor,axisYCoordinates);
}
