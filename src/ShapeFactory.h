#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED
#include <GL/glut.h>
#include<iostream>
#include <vector>
#include"Coordinate.h"
#include"Color.h"
using namespace std;
class ShapeFactory{
    public:
        void drawTriangle(std::vector<Color>, std::vector<Coordinate>&,bool);
        void drawPoint(Color, Coordinate&);
        void drawLine(std::vector<Color>, std::vector<Coordinate>&);
        void drawXYAxis(std::vector<Color>);
};

#endif // SHAPEFACTORY_H_INCLUDED
