#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

float xMin = -24,
      xMax = 24,
      zMin = 12,
      zMax = 60;
float desiredFPS = 30;
float X = xMax,
      XL = xMax;
float Z = zMin,
      ZL = zMax;
float rotationX = 25.0,
      rotationY = 0.0;
int last_x,
    last_y;
int width = 1200,
    height = 480;
float var = 0.0f,
      dir = 1.0f;
int count=0,
    distOrigem = 45,
    gridSize = 12;
char direction = 'x';

void init(void);
void display(void) ;
void idle(void);
void keyboard (unsigned char key, int x, int y);
void motion(int x, int y );
void mouse(int button, int state, int x, int y);
void grid(float xMax, float xStep, float xMin, float zMax, float zStep, float zMin);
void cubo(float x, float z);
void reshape(int w, int h);

float max(float a, float b)
{
  return a > b ? a : b;
}

float min(float a, float b)
{
  return a < b ? a : b;
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (width, height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  printf("Teclas W,A,S,D movimentam o cubo \n");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc( mouse );
  glutMotionFunc( motion );
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}

void init(void)
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  glEnable(GL_LIGHT0);                   
  glEnable(GL_COLOR_MATERIAL);           
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glEnable(GL_LIGHTING);                 
  glEnable(GL_DEPTH_TEST);               
  glEnable(GL_CULL_FACE);                

  glutSetWindowTitle("3D Board");
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(70.0, (GLfloat) width/(GLfloat) height, 1.0, 200.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity ();
  gluLookAt (0.0, 30.0, 0, 0.0, 0.0, 25.0, 0.0, 1.0, 0.0);

  grid(-30, gridSize, 30, 6, gridSize, 66);

  cubo(X, Z);

  glutSwapBuffers();
}

void cubo(float x, float z)
{

  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(x , gridSize/2, z);
    glutSolidCube(gridSize);
  glPopMatrix();
}

void grid(float xMax, float xStep, float xMin, float zMax, float zStep, float zMin)
{

  glPushMatrix();
    glColor3f (1.0, 1.0, 1.0);
    for(float i = xMax; i < xMin; i = i + xStep) {
      for(float j = zMax; j < zMin; j = j + zStep) {
        glBegin(GL_LINE_LOOP);
          glVertex3f(i, 0, j);
          glVertex3f(i + xStep, 0, j);
          glVertex3f(i + xStep, 0, j + zStep);
          glVertex3f(i, 0, j + zStep);
        glEnd();
      }
    }
  glPopMatrix();
}

bool movendo = false;

void updateMovement(float dt)
{
  float qtdMov = gridSize/10.0;
   switch (tolower(direction))
    {
    case 'w':
       Z = Z + qtdMov > zMax ? zMax : Z + qtdMov;
       movendo = Z != zMax;
    break;
    case 's':
    	Z = Z - qtdMov < zMin ? zMin : Z - qtdMov;
    	movendo = Z != zMin;
    break;
    case 'a':
        X = X + qtdMov > xMax ? xMax : X + qtdMov;
       movendo = X != xMax;
    break;
    case 'd':
        X = X - qtdMov < xMin ? xMin : X - qtdMov;
       movendo = X != xMin;
    break;
    }
  	if(abs(ZL - Z) >= gridSize - 0.01 || abs(XL - X) >= gridSize - 0.01) {
    	movendo = false;
    }
}

void idle ()
{  
  float t,
        desiredFrameTime,
        frameTime;
  static float tLast = 0.0;

    // Get elapsed time
  t = glutGet(GLUT_ELAPSED_TIME);
    // convert milliseconds to seconds
  t /= 1000.0;

    // Calculate frame time
  frameTime = t - tLast;
    // Calculate desired frame time
  desiredFrameTime = 1.0 / (float) (desiredFPS);

    // Check if the desired frame time was achieved. If not, skip animation.
  if( frameTime <= desiredFrameTime)
        return;
    /*
     *UPDATE ANIMATION VARIABLES
     */
   if(movendo) {
    updateMovement(frameTime);
  }

    /* Update tLast for next time, using static local variable */
  tLast = t;
  glutPostRedisplay();
}

void reshape (int w, int h) {
  width = w;
  height = h;
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard (unsigned char key, int x, int y) {
  if(movendo) {
    return;
  }
  movendo = true;
  direction=tolower(key);
  ZL = Z; XL = X;
}

// Motion callback
void motion(int x, int y )
{
  rotationX += (float) (y - last_y);
  rotationY += (float) (x - last_x);

  last_x = x;
  last_y = y;
}
// Mouse callback
void mouse(int button, int state, int x, int y)
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
}