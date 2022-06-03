#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <iostream>
using namespace std;

int windWidth = 1000, windHeight = 500;
int windID[3];
int windCount = 0, stepCount = 0;

char mergeSort[3][8] ={
                        '2', '1', '8', '6', '4', '3', '5', '7',
                        '1', '2', '6', '8', '3', '4', '5', '7',
                        '1', '2', '3', '4', '5', '6', '7', '8'
                    };

static void myInit()
{
    glClearColor(1.0, 1.0, 0.0, 0.8);
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

static void idle(void)
{
    glutPostRedisplay();
}

static void drawArrow()
{
    glPushMatrix();
    glLineWidth(3.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2i(500, 450);
        glVertex2i(500, 405);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2i(500, 400);
        glVertex2i(490, 410);
        glVertex2i(510, 410);
    glEnd();
    glPopMatrix();
    glFlush();
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
    printText(150, 460, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "ANGADI INSTITUTE OF TECHONOLOGY AND MANAGEMENT");
    printText(400, 430, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "BELGAVI-590009");
    printText(160, 400, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    printText(380, 320, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, "A 6 Semester Computer Graphics Mini-Project on");
    printText(400, 280, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, "MERGE SORT SIMULATION");
    printText(300, 200, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_10, "Submitted by :");
    printText(400, 180, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, "Shrinath Korajkar                      2AG19CS073");
    printText(400, 160, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, "Prathamesh Chougule               2AG19CS047");
    printText(350, 50, 1.0, 0.0, 0.0, GLUT_BITMAP_9_BY_15, "Press Q to                  Press N to next");
    glFlush();
}

static void rulesPage()
{
    glClear(GL_COLOR_BUFFER_BIT);
    printText(400, 460, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "GUIDE AND RULES");
    printText(300, 360, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, "1. Press Q to quit");
    printText(300, 320, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, "2. Press N to next");
    printText(300, 280, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, "3. Left Click to Start Simulation");
    printText(300, 240, 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18, "4. Right Click to Open Menu");
    glFlush();
}

static void displayArray(int startDigit, int endDigit)
{
    glColor3f(0.0, 1.0, 0.0);
    int next = 0;

    int startx = 375, endx = 405, starty = 480, endy = 450;
    // glPolygonMode(GL_FRONT, GL_LINE);

    glBegin(GL_QUADS);
        for(int i = startDigit; i <= endDigit; i++)
        {
            glVertex2i(startx + next, starty);
            glVertex2i(startx + next, endy);
            glVertex2i(endx + next, endy);
            glVertex2i(endx + next, starty);
            next += 32;
        }
    glEnd();
    next = 0;
    for(int i = startDigit; i <=endDigit; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(startx + next + 8, starty - 20);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mergeSort[stepCount][i - 1]);
        next += 32;
    }
}

static void layer1(int btm)
{
    glPushMatrix();
    glTranslatef(0, btm, 0);
    displayArray(1, 8);
    glPopMatrix();
}

static void layer2(int btm)
{
    glPushMatrix();
    glTranslatef(-175, btm, 0);
    displayArray(1, 4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(300, btm, 0);
    displayArray(5, 8);
    glPopMatrix();
}

static void layer3(int btm)
{
    glPushMatrix();
    glTranslatef(-285, btm, 0);
    displayArray(1, 2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, btm, 0);
    displayArray(3, 4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(190, btm, 0);
    displayArray(5, 6);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(475, btm, 0);
    displayArray(7, 8);
    glPopMatrix();
}

static void layer4(int btm)
{
    glPushMatrix();
    glTranslatef(-350, btm, 0);
    displayArray(1, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-185, btm, 0);
    displayArray(2, 2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-75, btm, 0);
    displayArray(3, 3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(95, btm, 0);
    displayArray(4, 4);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(135, btm, 0);
    displayArray(5, 5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(300, btm, 0);
    displayArray(6, 6);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(405, btm, 0);
    displayArray(7, 7);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(575, btm, 0);
    displayArray(8, 8);
    glPopMatrix();
}
static void layerDisplay()
{
    stepCount = 0;
    layer1(0);
    layer2(-65);
    layer3(-130);
    layer4(-195);
    stepCount++;
    layer3(-260);
    layer2(-335);
    stepCount++;
    layer1(-390);
    printText(400, 20, 1.0, 0.0, 0.0, GLUT_BITMAP_9_BY_15, "TIME COMPLEXITY : O(n)");
    drawArrow();
}

static void mergeSimulation()
{
    glClear(GL_COLOR_BUFFER_BIT);

    layerDisplay();

    glFlush();
}

static void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q' :
        case 'Q' :
            exit(0);
            break;

        case 'n' :
        case 'N' :
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
            else{
                windCount = 0;
                glutSetWindow(windID[0]);
            }

            glutShowWindow();
            break;
    }

    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    cout<<x<<" "<<500 - y<<endl;
}

static void helpMenu(int response)
{
    switch(response)
    {
        case 1:
                exit(0);
                break;

        case 2:
                keyBoard('n', 1, 1);
                break;

        case 3:
                windCount++;
                keyBoard('n', 1, 1);
                break;

        case 4:
                mergeSimulation();
                break;

        case 5:
                break;
    }
}

static void createMenu()
{
    glutCreateMenu(helpMenu);
    glutAddMenuEntry("QUIT",1);
    glutAddMenuEntry("HOME",2);
    glutAddMenuEntry("RULES",3);
    glutAddMenuEntry("START SIMULATION",4);
    glutAddMenuEntry("STOP SIMULATION",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    glutKeyboardFunc(keyBoard);
    glutMouseFunc(mouse);
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
    glutDisplayFunc(mergeSimulation);
    glutHideWindow();
    createMenu();

    glutSetWindow(windID[1]);
    laterWindowCreation();
    glutDisplayFunc(rulesPage);
    glutHideWindow();

    glutSetWindow(windID[0]);
    laterWindowCreation();
    glutDisplayFunc(frontPage);
    glutShowWindow();

    // delete this after over
    glutSetWindow(windID[2]);
    glutShowWindow();

    glutMainLoop();
    return EXIT_SUCCESS;
}
