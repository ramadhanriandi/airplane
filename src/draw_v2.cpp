#include <iostream>
#include "OpenGLModel.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 500

int main(int argc, char **argv) {
    OpenGLModel myModel;
    myModel.loadObj("../files/plane.obj");
    myModel.init(WIDTH, HEIGHT);
    myModel.setDelay(25);
    myModel.scaleModel(0.5f, 0.5f, 0.5f);
    myModel.run();

    return 0;
}