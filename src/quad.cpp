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
#include<iostream>

void display(void);
void init (void);
void keyboard(unsigned char key, int x, int y);

using namespace std;
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (600, 400);
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
   // Desenhar um polígono branco (retângulo)
    ShapeFactory f;
    Coordinate co1(0.25, 0.25, 0.0),co2(0.75, 0.75, 0.0), co3(0.25, 0.75, 0.0);
    list<Coordinate> coordinates{co1,co2,co3};
    f.drawTriangle(COLOR_RED, coordinates);

   glutSwapBuffers ();
}


void init (void)
{
   // selecionar cor de fundo (preto)
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
      case 27:
         exit(0);
      break;
   }
}
