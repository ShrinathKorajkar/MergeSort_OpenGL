#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

int windWidth = 1000, windHeight = 500;
int windID[3];
static void configureWindow();
int windCount = 0;

static void myInit()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glViewport(0,0, windWidth, windHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windWidth, 0, windHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void resize(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,(double)width, 0, (double)height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    windWidth = width;
    windHeight = height;
}


static void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q' || 'Q':
            exit(0);
            break;

        case 'n':
            windCount++;
            glutHideWindow();

            if(windCount == 1)
            {
                glutSetWindow(windID[1]);
            }
            else if(windCount == 2)
            {
                glutSetWindow(windID[2]);
            }

            glutShowWindow();
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void printText(int x, int y, float r, float g, float b, void *font, char *str)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(str);
    for(i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

static void frontPage()
{
    glClear(GL_COLOR_BUFFER_BIT);
    printText(200, 400, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "hello world");
    glFlush();
}

static void beforeWindowCreation()
{
    glutInitWindowSize(windWidth,windHeight);
    glutInitWindowPosition(120,60);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
}
/* Program entry point */
static void laterWindowCreation()
{
    myInit();
    glutReshapeFunc(resize);
    glutDisplayFunc(frontPage);
    glutKeyboardFunc(keyBoard);
    glutIdleFunc(idle);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    beforeWindowCreation();

    windID[0] = glutCreateWindow("HOME");
    windID[1] = glutCreateWindow("GUIDE AND RULES");
    windID[2] = glutCreateWindow("MERGE SORT SIMULATION");
    laterWindowCreation();
    glutHideWindow();

    glutSetWindow(windID[1]);
    laterWindowCreation();
    glutHideWindow();

    glutSetWindow(windID[0]);
    laterWindowCreation();
    glutShowWindow();

    glutMainLoop();
    return EXIT_SUCCESS;
}
