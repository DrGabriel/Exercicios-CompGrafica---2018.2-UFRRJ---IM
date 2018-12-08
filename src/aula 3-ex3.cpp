/*
  Name:        mousekeyboard.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:       10/07/2018
  Updates:		18/12/2014 - Scroll up and down added
					10/04/2014 - Passive motion added
  Description: Simple OpenGL program that captures mouse and keyboard
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

int windowSizeX = 640;
int windowSizeY = 640;
float objectPosX = -3.0;
float objectPosY = -3.0;

float objectRadius = 0.5;

int speed = 3;
int moveX = 0;
int moveY = 0;
bool passiveMotion = false;


void drawBoard(int w, int h, int n, int m) {
  bool color = true;
  //for each width and height draw a rectangle with a specific color
  for(int i = -3; i < n+w; ++i) {
    for(int j = -3; j < m+h; ++j) {
      //oscillate the color per square of the board
      if(color)
        glColor3f(1, 1, 1);
      else
        glColor3f(0, 0, 0);
      color = !color;

      //draw a rectangle in the ith row and jth column
      glRecti(i, j, i+w, j+h);
    }
    //if(m % 2 == 0) color = !color; //switch color order at end of row if necessary
  }
}
// Special Keys callback
void specialKeysRelease(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT :
			moveX = 0;
		break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN :
			moveY = 0;
		break;
	}
	glutPostRedisplay();
}


// Motion callback
void motion(int x, int y )
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
	y = windowSizeY - y;

	objectPosX = x;
	objectPosY = y;
}

// Motion callback
void noMotion(int x, int y )
{
	// Cancel passive motion
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
	// Inverte mouse para que origem fique no canto inferior esquerdo da janela
	// (por default, a origem é no canto superior esquerdo)
    y = windowSizeY - y;
    float x1=(((float) x/windowSizeX)*6.0)-3.0 ;
    float y1= (((float)y/windowSizeY)*6.0)-3.0;
	if ( button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			printf("\nBotao esquerdo pressionado na posicao [%f, %f].", x1, y1);
			objectPosX = x1;
			objectPosY = y1;
		}
		else
			printf("\nBotao esquerdo solto na posicao [%f, %f].", x1, y1);  // GLUT_UP
	}
	if ( button == GLUT_RIGHT_BUTTON)
	{
		printf("\nBotao direito do mouse pressionado.");
	}
   if(button == 3) // Scroll up
   {
		printf("\nScroll up.");
   }
   if(button == 4) // Scroll Down
   {
		printf("\nScroll down.");
	}
}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // Clean z-buffer
    float i=-3.0,j=-3.0;
    bool found = false;
    for(i;i<=2.5 ;i+=1.0){
        for(j=-3.0;j<=2.5;j+=1.0){
            if (objectPosX >= i && objectPosX< (i + 1.0) && objectPosY >= j && objectPosY < j + (1.0)){

                 objectPosX = i + 0.5;
                 objectPosY = j + 0.5;
                found = true;
                break;
            }
            if(found)
                break;
        }
    }
	// Change object position if some key is pressed
    drawBoard(1,1,3,3);
	glPushMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(objectPosX, objectPosY, 0.0f);
	//glRecti(objectPosX, objectPosY, objectPosX+10.0, objectPosY+10.0);
	glutSolidSphere(objectRadius, 100, 10);
	glPopMatrix();

	glutSwapBuffers ();  // Required when double buffer is initialized
	glutPostRedisplay();
}


void init (void)
{
	glClearColor (0.4, 0.4, 0.4, 0.0);

	// inicializar sistema de viz.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -500.0, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main Function
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (windowSizeX, windowSizeY);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	init ();

	// Modifique aqui para '0' para aumentar o delay
	glutIgnoreKeyRepeat(1);
	glutMouseFunc( mouse );


	glutDisplayFunc(display);




	glutMainLoop();

	return 0;
}
