/*
  Name:        quad.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:        10/07/2018
  Release:     18/09/2004
  Description: Simple opengl program
*/

#include <stdio.h>
#include <GL/glut.h>
#include "ShapeFactory.h"
#include "Coordinate.h"
#include "Colors.h"
#include<list>
#include <vector>
#include<iostream>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);
int drawOption = 0;
const int optionA = 0,
          optionB = 1,
          optionC = 2,
          optionD = 3;
float z = 0.0;
float x1 = 0.5, x2 = 0.95, x3 = (x2 + x1)/2, x4 = 1 - x2 , x5 = (x4 + x1)/2 , y1 = 0.5, y2 = 0.95, y3 = 1 - y2;
Coordinate co1(x1, y1, z),co2(x2, y1, z), co3(x3, y2, z), co4(x4, y1, z) , co5(x5,y3,z);
using namespace std;
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (400, 400);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Quad Test");
   init ();
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);

	printf("Pressione ESC para fechar.\n");

   glutMainLoop();

   return 0;
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT);
    ShapeFactory f;

    vector<Coordinate> triangleCoordinates1 = {co1,co2,co3};
    vector<Coordinate> triangleCoordinates2 = {co1,co4,co5};
    vector<Color> colors (3,COLOR_RED);
    vector<Color> colorAxis (4,COLOR_GREEN);
    f.drawXYAxis(colorAxis);

    switch(drawOption){

        case optionA:
            f.drawTriangle(colors, triangleCoordinates1,true);
        break;

        case optionB:
            f.drawTriangle(colors, triangleCoordinates1,false);
        break;

        case optionC:
            f.drawTriangle(colors, triangleCoordinates1,false);
            f.drawTriangle(colors, triangleCoordinates2,true);
        break;

        case optionD:

            float x1 = 0.25, x1Middle = (0.5*x1), x2 = x1 + x1Middle, x3 = 3*x1, x4 = x3 - x1Middle,
                  y1 = 0.5,  yMiddle = (0.5*y1),  y2 = y1 + yMiddle,  y3 = y1 - yMiddle;

            Coordinate c1(x2,y2,z), c2(x1,y1,z), c3(x2,y3,z), c4(x4,y3,z), c5(x3,y1,z), c6(x4,y2,z);
            vector<Color> color (2,COLOR_BLUE);

            vector<Coordinate> coordinates1 = {c1,c2};
            vector<Coordinate> coordinates2 = {c2,c3};
            vector<Coordinate> coordinates3 = {c3,c4};
            vector<Coordinate> coordinates4 = {c4,c5};
            vector<Coordinate> coordinates5 = {c5,c6};

            f.drawLine(color,coordinates1);
            f.drawLine(color,coordinates2);
            f.drawLine(color,coordinates3);
            f.drawLine(color,coordinates4);
            f.drawLine(color,coordinates5);

        break;

    }


   glutSwapBuffers ();
}


void init (void)
{
   // selecionar cor de fundo (branco)
   glClearColor (1.0, 1.0, 1.0, 1.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Inicializa com matriz identidade
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
      case 'a':
        drawOption = optionA;
        glutPostRedisplay();
      break;
      case 'b':
        drawOption = optionB;
        glutPostRedisplay();
      break;
      case 'c':
        drawOption = optionC;
        glutPostRedisplay();
      break;
      case 'd':
        drawOption = optionD;
        glutPostRedisplay();
      break;
      case 27:
         exit(0);
      break;
   }
}
