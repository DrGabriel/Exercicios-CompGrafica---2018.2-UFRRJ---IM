#ifndef SHAPEFACTORY_H_INCLUDED
#define SHAPEFACTORY_H_INCLUDED
#include <GL/glut.h>
#include<iostream>
#include<list>
#include"Coordinate.h"
#include"Color.h"
using namespace std;
class ShapeFactory{
    public:
        void drawTriangle(Color, list<Coordinate>&);
        void drawVertext(void);
};

#endif // SHAPEFACTORY_H_INCLUDED
