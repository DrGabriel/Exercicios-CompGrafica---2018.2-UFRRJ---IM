/*
  Name:        quad_transform.cpp
  Copyright:   Version 0.1
  Author:      Rodrigo Luis de Souza da Silva
  Edited:	   Bruno José Dembogurski
  Update:      10/07/2018
  Date:        16/09/2004
  Description: Transformations using of OpenGL commands
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float angle = 0, objectScale = 3.5;
float xtrans = 0, ytrans = 0, ztrans = 0;
int enableMenu = 0;

int windowSizeX = 640;
int windowSizeY = 640;
float objectPosX = windowSizeX/2;
float objectPosY = windowSizeY/2;

int objectRadius = 50;

int speed = 1;
int moveX = 0;
int moveY = 0;
bool passiveMotion = false;
void display(void);
void init (void);
void desenhaEixos();
void mouse(int button, int state, int x, int y);
// Special Keys callback
void specialKeysPress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			moveY = speed;
		break;
		case GLUT_KEY_DOWN:
			moveY = -speed;
		break;
		case GLUT_KEY_RIGHT:
			moveX = speed;
		break;
		case GLUT_KEY_LEFT:
			moveX = -speed;
	break;
		default:
			printf("\nPressionou outra tecla especial não mapeada!");
	break;
	}
	glutPostRedisplay();
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




// Keyboard callback
void keyboardPress(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
		break;
		case '+':
			if(objectScale<=100)
			{
				printf("\nAumentando tamanho do quadrado (%d)", objectScale);
				objectScale+=0.1;
			}
			else
				printf("\nTamanho máximo atingido (%d)", objectScale);
		break;
		case '-':
			if(objectScale>1.0)
			{
				printf("\nDiminuindo tamanho do quadrado (%d)", objectScale);
				objectScale-=0.1;
			}
			else
				printf("\nRaio mínimo atingido (%d)", objectScale);
		break;
		case 'w':
			moveY = speed;
		break;
		case 's':
			moveY = -speed;
		break;
		case 'd':
			moveX = speed;
		break;
		case 'a':
			moveX = -speed;
		break;
        case 'R':
			angle += speed;
		break;
        case 'r':
			angle -= speed;
		break;
		case 'm':
			passiveMotion = !passiveMotion;

			if(passiveMotion)
			{
				printf("\n\"Passive Motion LIGADO");
				glutPassiveMotionFunc( motion );
			}
			else
			{
				printf("\n\"Passive Motion DESLIGADO");
				glutPassiveMotionFunc( NULL );
			}
		break;
		default:
			printf("\nUma tecla não mapeada foi pressionada");
		break;
	}
}

// Keyboard callback
void keyboardRelease(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w' :
		case 's' :
			moveY = 0;
		break;
		case 'd' :
		case 'a' :
			moveX = 0;
		break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
   glutInitWindowSize (windowSizeX, windowSizeY);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("exericio 4");
   glutIgnoreKeyRepeat(1);
	glutMouseFunc( mouse );

	glutKeyboardFunc( keyboardPress );
	glutKeyboardUpFunc( keyboardRelease );

	glutSpecialFunc( specialKeysPress );
	glutSpecialUpFunc( specialKeysRelease );

	glutDisplayFunc(display);
	glutMotionFunc( motion );
	glutPassiveMotionFunc( NULL );
   init ();
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
   if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      enableMenu = 1;
}



void desenhaEixos()
{
   glColor3f (0.0, 1.0, 0.0);
   glBegin(GL_LINES);
      glVertex2f (0.0, -100.0);
      glVertex2f (0.0, 100.0);
      glVertex2f (-100.0, 0.0);
      glVertex2f (100.0, 0.0);
   glEnd();
}

void display(void)
{
   // Limpar todos os pixels
   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glLoadIdentity(); // Inicializa com matriz identidade

   desenhaEixos();

   glColor3f (1.0, 0.0, 0.0);
   xtrans+=moveX;
   ytrans+=moveY;
   glPushMatrix();
      glTranslatef(xtrans, ytrans, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glScalef(objectScale, objectScale, objectScale);
      glutWireCube(10);
   glPopMatrix();

   glutSwapBuffers ();
   glutPostRedisplay();

}

void init (void)
{
   // selecionar cor de fundo (preto)
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // inicializar sistema de viz.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
