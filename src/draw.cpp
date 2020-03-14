#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include "cube.h"

using namespace std;

GLfloat xRotated, yRotated, zRotated;

void init(void) {
    glClearColor(0,0,0,0);
}

void DrawCube(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    glBegin(GL_QUADS);

    // for (int i = 0; i < N_VERTEX; i+=3) {
    //     float firstVertex = cubePositions[i];
    //     float secondVertex = cubePositions[i + 1];
    //     float thirdVertex = cubePositions[i + 2];
    //     glVertex3f(firstVertex, secondVertex, thirdVertex);
    // }

    // // glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    // // glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    // // glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    // // glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    // // glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    // // glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
    glEnd();

    glFlush();
}

void animation(void) {
    yRotated += 0.01;
    xRotated += 0.02;
    DrawCube();
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}

int main(int argc, char** argv) {
    cout << cubePositions[0] << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);
    glutMainLoop();

    return 0;
}