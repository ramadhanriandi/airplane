#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>
#include <math.h>
#include "plane.c"
#include "color.c"

using namespace std;

GLfloat xRotated = 0, yRotated = 0, zRotated = 0;

float lx = 0.0f, ly = 0.0f, lz = -1.0f;

float phi = 0.0f;
float theta = 0.0f;
float temp_x,temp_y,temp_z;
// XZ position of the camera
float x = 0.0f, y = 0.0, z = 40.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

float rotateValue = 3;
// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red = 1.0f, blue = 1.0f, green = 1.0f;

// angle for rotating triangle

static bool shade = false;

GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat lightPos[] ={10,0,-15,1};

  //The color of the sphere
GLfloat materialColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
//The specular (shiny) component of the material
GLfloat materialSpecular[] = {0,0,1,1};
//The color emitted by the material
GLfloat materialEmission[] = {1.0f,1.0f,0, 1.0f};

GLfloat shininess = 20;

void reset_display()
{
    xRotated = 0;
    yRotated = 0;
    zRotated = 0;
    x = 0.0f;
    y = 0.0;
    z = 40.0f;
    phi = 0.0f;
    theta = 0.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    lx = 0.0f;
    ly = 0.0f;
    lz = -1.0f;
    shade = false;
}

void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.5f;
    float epsilon = 0.1f;
    // printf("x : %f z : %f theta : %f\n",x,z,theta);
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
        //lz = -cos(theta);

        // lx = -sin(theta) * cos(phi);
        // ly = -sin(theta) * sin(phi);
        // lz = -cos(theta);
        upX = sin(phi);
        upY = cos(phi);
        upZ = sin(phi);


        break;
    case '2':
        //putar kanan
        phi -= 0.1;
        upX = sin(phi);
        upY = cos(phi);
        upZ = sin(phi);

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
		glDisable(GL_COLOR_MATERIAL);
		//Diffuse (non-shiny) light component
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		//Specular (shiny) light component
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter
	}else{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		GLdouble(GL_NORMALIZE);
		//Disable color materials, so that glMaterial calls work
		glEnable(GL_COLOR_MATERIAL);
	}
    // glTranslatef(0.0, 0.0, -10.5);
    // glutSolidCube(6);
    glBegin(GL_QUADS);

    int numberOfVertex = sizeof(planePositions) / sizeof(*planePositions);

    int counterColorUsed = 0;
    int indexColorUsed = 0;
    for (int i = numberOfVertex - 1; i >= 0; i -= 3)
    {
        float firstVertex = planePositions[i - 2];
        float secondVertex = planePositions[i - 1];
        float thirdVertex = planePositions[i];
        glVertex3f(firstVertex, secondVertex, thirdVertex);
        if ((numberOfVertex - i - 1) % 12 == 0) {
            counterColorUsed++;

            float red = colorShapes[3*indexColorUsed];
            float green = colorShapes[3*indexColorUsed+1];
            float blue = colorShapes[3*indexColorUsed+2];
            glColor3f(red, green, blue);

            if (counterColorUsed == 6) {
                counterColorUsed = 0;
                indexColorUsed ++;
            }
        }
    }

    glPopMatrix();
    glEnd();

    glFlush();
}

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

void menuHelp(){
    cout<<"LIST OF COMMANDS : "<<endl;
    cout<<"KEY_LEFT / KEY_RIGHT : Menggerakkan kamera mengitari model"<<endl;
    cout<<"KEY_UP / KEY_DOWN : Mengubah jarak kamera"<<endl;
    cout<<"U/J : Rotasi objek pada sumbu x"<<endl;
    cout<<"I/K : Rotasi objek pada sumbu y"<<endl;
    cout<<"O/L : Rotasi objek pada sumbu z"<<endl;
    cout<<"1/2 : Rotasi kamera terhadap vektor up"<<endl;
    cout<<"0 : reset view"<<endl;
    cout<<"space : on/off shading"<<endl;
    cout<<"esc : exit window"<<endl;

}

int main(int argc, char **argv)
{
    menuHelp();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(720, 720);
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


