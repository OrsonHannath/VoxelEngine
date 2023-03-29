#include "OpenGLApp.h"


// Window Settings
int windowWidth = 1200;
int windowHeight = 600;

int main(int argc, char* args[]) {

    OpenGLApp openGlApp;

    return openGlApp.OnExecute(windowWidth, windowHeight);
}
