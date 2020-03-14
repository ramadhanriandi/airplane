#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include <math.h>
#include "plane.c"

using namespace std;

GLfloat xRotated = 0, yRotated = 0, zRotated = 0;

float lx = 0.0f, ly =0.0f ,lz = -1.0f;
// XZ position of the camera
float x = 0.0f, y =0.0,z = 5.0f;

float rotateValue = 1;
// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red = 1.0f, blue = 1.0f, green = 1.0f;

// angle for rotating triangle
float angle = 0.0f;

void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.1f;

    switch (key)
    {
    case GLUT_KEY_UP:
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
}

void processNormalKeys(unsigned char key, int x, int y)
{

    float fraction = 0.1f;

    switch (key)
    {
            case 27:
        exit(0);
    case 'u':
        xRotated += rotateValue;
        break;
    case 'j':
        xRotated -= rotateValue;
        break;
    case 'i':
        yRotated += rotateValue;
        break;
    case 'k':
        yRotated -= rotateValue;
        break;
    case 'o':
        zRotated += rotateValue;
        break;
    case 'l':
        zRotated -= rotateValue;
        break;
    }
}

void init(void)
{
    glClearColor(0, 0, 0, 0);
}

void DrawCube(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    gluLookAt(x, y, z,
              x + lx, y+ly, z + lz,
              0.0f, 1.0f, 0.0f);

    glRotated(xRotated, 1.0, 0.0, 0.0);
    glRotated(yRotated, 0.0, 1.0, 0.0);
    glRotated(zRotated, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -10.5);

    glBegin(GL_QUADS);

    int numberOfVertex = sizeof(planePositions) / sizeof(*planePositions);

    for (int i = numberOfVertex - 1; i >= 0; i -= 3)
    {
        float firstVertex = planePositions[i - 2];
        float secondVertex = planePositions[i - 1];
        float thirdVertex = planePositions[i];
        glVertex3f(firstVertex, secondVertex, thirdVertex);
    }

    glColor3f(0.0f, 1.0f, 0.0f); // Color Blue
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f, 0.5f, 0.0f); // Color Orange
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f, 0.0f, 0.0f); // Color Red
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f, 1.0f, 0.0f); // Color Yellow
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f, 0.0f, 1.0f); // Color Blue
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f, 0.0f, 1.0f); // Color Violet
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
    glPopMatrix();
    glEnd();

    glFlush();
}

// void animation(void)
// {
//     yRotated += 0.01;
//     xRotated += 0.02;
//     DrawCube();
// }

// void reshape(int x, int y)
// {
//     if (y == 0 || x == 0)
//         return;
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
//     glMatrixMode(GL_MODELVIEW);
//     glViewport(0, 0, x, y);
// }

void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(DrawCube);
    glutReshapeFunc(changeSize);
    glutIdleFunc(DrawCube);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}