/*
  Name:        exericio2.cpp
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
#include<math.h>
#include <vector>
#include<iostream>

#define PI 3.14159265

void display(void);
void init (void);
void drawSin(int parts, ShapeFactory& f);
void keyboard(unsigned char key, int x, int y);
int drawOption = 0;
const int optionA = 0,
          optionB = 1,
          optionC = 2;
float z =0.0;
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
    vector<Coordinate> xAxis = {Coordinate(-10.0,0.0,z), Coordinate(390.0,0.0,z)};
    vector<Coordinate> yAxis = {Coordinate(0.0,-2,z), Coordinate(0.0,2,z)};
    f.drawLine(vector<Color>(4,COLOR_WHITE),xAxis);
    f.drawLine(vector<Color>(4,COLOR_WHITE),yAxis);

    drawSin(300,f);

   glutSwapBuffers ();
}


void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);              // Seleciona Matriz de Projeção
   glLoadIdentity();
   glOrtho(-10.0, 390, -2, 2, -1.0, 1.0);

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
      case 27:
         exit(0);
      break;
   }

}

   void drawSin(int parts, ShapeFactory& f){
        float angleSize = 360.0/parts;
        float i = 0.0;
        float radians = PI/180;
        Coordinate co1(i,sin(i*radians),z);
        for(float i = angleSize; i <= 360.0 ; i+= angleSize){
             Coordinate co2(i,sin(i*radians),z);
             vector<Coordinate> coordinates = {co1,co2};
            f.drawLine(vector<Color>(4,COLOR_GREEN), coordinates);
            co1 = co2;

        }
   }
