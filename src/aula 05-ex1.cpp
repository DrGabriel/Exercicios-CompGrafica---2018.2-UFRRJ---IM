#include <iostream>
#include <stdio.h>
#include <GL/glut.h>

using namespace std;

float desiredFPS = 5;

float x_Verde = 0.3, y_Verde = 0.5,
    dirX_Verde = 0.1, dirY_Verde = 0.1;

const float maiorXVerde = 0.7, maiorYVerde = 0.5,
    menorXVerde = 0.2, menorYVerde = 0.2;

float x_Vermelho = 0.2, y_Vermelho = 0.2,
    dirX_Vermelho = 0.1, dirY_Vermelho = 0.1;

const float maiorX_Vermelho = 0.8, maiorY_Vermelho = 0.8,
    menorX_Vermelho = 0.4, menorY_Vermelho = 0.5;

void display(void);
void init (void);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

void idle()
{
    float t, desiredFrameTime, frameTime;
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
    
    if(maiorX_Verde + x_Verde >= 1 || menorX_Verde + x_Verde <= 0.1) 
        dirX_Verde *= -1;
    if(maiorY_Verde + y_Verde >= 1 || menorY_Verde + y_Verde <= 0.1) 
        dirY_Verde *= -1;
    //else if ()
    x_Verde += dirX_Verde;
    y_Verde += dirY_Verde;

    if(maiorX_Vermelho + x_Vermelho >= 1 || menorX_Vermelho + x_Vermelho <= 0) 
        dirX_Vermelho *= -1;
    if(maiorY_Vermelho + yT_Vermelho >= 1 || menorY_Vermelho + y_Vermelho <= 0) 
        dirY_Vermelho *= -1;
    //else if ()
    x_Vermelho += dirX_Vermelho;
    y_Vermelho += dirY_Vermelho;

    
    /* Update tLast for next time, using static local variable */
    tLast = t;

    glutPostRedisplay();

}

void plotTriangle (float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f (x1, y1);
        glVertex2f (x2, y2);
        glVertex2f (x3, y3);
    glEnd();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    glColor3f (0.0, 1.0, 0.0);

    glPushMatrix();
        glTranslatef(x_Verde, y_Verde, 0);
        glBegin(GL_TRIANGLES);
            plotTriangle(0.5, menorY_Verde, maiorX_Verde, 0.4, menorX_Verde, maiorY_Verde);
        glEnd();
    glPopMatrix();

    glColor3f (1.0, 0.0, 0.0);

    glPushMatrix();
        glTranslatef(x_Vermelho, y_Vermelho, 0);
        plotTriangle(0.6, maiorY_Vermelho, maiorX_Vermelho, menorY_Vermelhoelho, menorX_Vermelho, 0.6);
    glPopMatrix();
    
    glutSwapBuffers ();
}

void init (void)
{
    // selecionar cor de fundo (preto)
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // inicializar sistema de viz.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Screensaver");
    glutFullScreen();
    glutIdleFunc( idle);
    init ();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
