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

float lx = 0.0f, ly = 0.0f, lz = -1.0f;

float phi = 0.0f;
float theta = 0.0f;
float temp_x,temp_y,temp_z;
// XZ position of the camera
float x = 0.0f, y = 0.0, z = 5.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

float rotateValue = 3;
// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red = 1.0f, blue = 1.0f, green = 1.0f;

// angle for rotating triangle

static bool shade = false;

GLfloat lightAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
// GLfloat lightColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightPos[] ={10,10,-15,0};
GLfloat lightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat lightSpecullar[] = {0.0f,0.0f,0.0f,0.0f};


  //The color of the sphere
//GLfloat materialColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
//The specular (shiny) component of the material
GLfloat materialSpecular[] = {0,0,0,1};
//The color emitted by the material
GLfloat materialEmission[] = {1.0f,0.0f,0, 1.0f};
GLfloat materialAmbient[] = {0.7f,0.7f,0.7f,1.0f};
GLfloat materialDiffuse[] = {0.8f,0.8f,0.8f,1.0f};


GLfloat shininess[] = {100};

void reset_display()
{
    xRotated = 0;
    yRotated = 0;
    zRotated = 0;
    x = 0.0f;
    y = 0.0;
    z = 5.0f;
    phi = 0.0f;
    theta = 0.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    lx = 0.0f;
    ly = 0.0f;
    lz = -1.0f;
}

void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.5f;
    float epsilon = 0.1f;
    printf("x : %f z : %f theta : %f\n",x,z,theta);
    switch (key)
    {
    case GLUT_KEY_UP:
        x += lx * fraction;
        y += ly * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        y -= ly * fraction;
        z -= lz * fraction;
        break;
    case GLUT_KEY_RIGHT:
        theta += 0.1;
        // phi += 0.5;
        
        temp_x = sqrt(x * x + z * z + y * y) * sin(theta) * cos(phi);
        temp_y = sqrt(x * x + z * z + y * y) * sin(theta) * sin(phi);
        temp_z = sqrt(x * x + z * z + y * y) * cos(theta);

        x = temp_x;
        y = temp_y;
        z = temp_z;
        lx = -sin(theta) * cos(phi);
        ly = -sin(theta) * sin(phi);
        lz = -cos(theta);

        break;
    case GLUT_KEY_LEFT:
        theta -= 0.1;
        // phi -= 0.5;
        temp_x = sqrt(x * x + z * z + y * y) * sin(theta) * cos(phi);
        temp_y = sqrt(x * x + z * z + y * y) * sin(theta) * sin(phi);
        temp_z = sqrt(x * x + z * z + y * y) * cos(theta);

        x = temp_x;
        y = temp_y;
        z = temp_z;

        lx = -sin(theta) * cos(phi);
        ly = -sin(theta) * sin(phi);
        lz = -cos(theta);
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
    case ' ':
        shade = !(shade);
        break;
    case '0':
        reset_display();   
        break;
    case '1':
        // putar kiri
        phi += 0.1;
        upX = sin(phi);
        upY = cos(phi);
        break;
    case '2':
        //putar kanan
        phi -= 0.1;
        upX = sin(phi);
        upY = cos(phi);
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
              x + lx, y + ly, z + lz,
              upX, upY, upZ);

    glRotated(xRotated, 1.0, 0.0, 0.0);
    glRotated(yRotated, 0.0, 1.0, 0.0);
    glRotated(zRotated, 0.0, 0.0, 1.0);
    
	if (shade){
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		//Disable color materials, so that glMaterial calls work
		glEnable(GL_COLOR_MATERIAL);
		//Diffuse (non-shiny) light component
		//Specular (shiny) light component
        glLightfv(GL_LIGHT0,GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecullar);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
		// glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess[0]); //The shininess parameter
	}else{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		GLdouble(GL_NORMALIZE);
		//Disable color materials, so that glMaterial calls work
		glDisable(GL_COLOR_MATERIAL);
	}
    // glTranslatef(0.0, 0.0, -10.5);
    // glutSolidCube(6);
    glBegin(GL_QUADS);

    int numberOfVertex = sizeof(planePositions) / sizeof(*planePositions);

    // for (int i = numberOfVertex - 1; i >= 0; i -= 3)
    // {
    //     float firstVertex = planePositions[i - 2];
    //     float secondVertex = planePositions[i - 1];
    //     float thirdVertex = planePositions[i];
    //     glVertex3f(firstVertex, secondVertex, thirdVertex);
    // }

    
    glVertex3d(-0.303567f,-1.00389f,-2.23275f);
    glVertex3d(0.246057f,-1.00411f,-2.23275f);
    glVertex3d(0.246057f,-1.00383f,-3.06f);
    glVertex3d(-0.303567f,-1.00343f,-3.06f);
    glVertex3d(-0.303567f,-1.00389f,-2.23275f);
    glVertex3d(0.246057f,-1.00411f,-2.23275f);
    glVertex3d(0.489108f,-0.761196f,-1.98973f);
    glVertex3d(-0.546343f,-0.761196f,-1.98973f);
    glVertex3d(0.246057f,-1.00383f,-3.06f);
    glVertex3d(-0.303567f,-1.00343f,-3.06f);
    glVertex3d(-0.546343f,-0.760023f,-3.3028f);
    glVertex3d(0.489108f,-0.761196f,-3.3028f);
    glVertex3d(-0.303567f,-1.00389f,-2.23275f);
    glVertex3d(-0.303567f,-1.00343f,-3.06f);
    glVertex3d(-0.546343f,-0.760023f,-3.3028f);
    glVertex3d(-0.546343f,-0.761196f,-1.98973f);
    glVertex3d(0.246057f,-1.00411f,-2.23275f);
    glVertex3d(0.246057f,-1.00383f,-3.06f);
    glVertex3d(0.489108f,-0.761196f,-3.3028f);
    glVertex3d(0.489108f,-0.761196f,-1.98973f);
    glVertex3d(-0.546343f,-0.761196f,-1.98973f);
    glVertex3d(0.489108f,-0.761196f,-1.98973f);
    glVertex3d(0.489108f,-0.761196f,-3.3028f);
    glVertex3d(-0.546343f,-0.760023f,-3.3028f);
    glVertex3f(-0.546343, -0.761196, -1.98973);
    glVertex3f(0.489108, -0.761196, -1.98973);
    glVertex3f(0.489242, 0.666667, -1.98962);
    glVertex3f(-0.546209, 0.666667, -1.98962);

    glVertex3f(-0.546343, -0.760023, -3.3028);
    glVertex3f(0.489108, -0.761196, -3.3028);
    glVertex3f(0.489242, 0.666667, -3.3027);
    glVertex3f(-0.546209, 0.666667, -3.3027);

    glVertex3f(-0.546209, 0.666667, -1.98962);
    glVertex3f(-0.546343, -0.761196, -1.98973);
    glVertex3f(-0.546343, -0.760023, -3.3028);
    glVertex3f(-0.546209, 0.666667, -3.3027);

    glVertex3f(0.489108, -0.761196, -1.98973);
    glVertex3f(0.489242, 0.666667, -1.98962);
    glVertex3f(0.489242, 0.666667, -3.3027);
    glVertex3f(0.489108, -0.761196, -3.3028);

    glVertex3f(-0.546343, -0.761196, -1.98973);
    glVertex3f(0.489108, -0.761196, -1.98973);
    glVertex3f(0.489108, -0.761196, -3.3028);
    glVertex3f(-0.546343, -0.760023, -3.3028);

    glVertex3f(-0.546209, 0.666667, -1.98962);
    glVertex3f(0.489242, 0.666667, -1.98962);
    glVertex3f(0.489242, 0.666667, -3.3027);
    glVertex3f(-0.546209, -0.524696, -3.3027);










    // glutSolidSphere(1,16,16);
    // glColor3f(0.0f, 1.0f, 0.0f); // Color Blue
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    // glColor3f(1.0f, 0.5f, 0.0f); // Color Orange
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(0.5f, 0.2f, 0.1f); // Color Red
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    // glColor3f(1.0f, 1.0f, 0.0f); // Color Yellow
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    // glColor3f(0.0f, 0.0f, 1.0f); // Color Blue
    // glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    // glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    // glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    // glColor3f(1.0f, 0.0f, 1.0f); // Color Violet

    // glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    // glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    // glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
    // glColor3f(1.0f, 0.0f, 0.0f); // Color Red

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