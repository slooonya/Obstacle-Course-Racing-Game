#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "vector"

using namespace std;


//================ Projection and Viewport Setting =============================
void setOrthoProjection() { // Setting for the menus and text
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void resetPerspectiveProjection() { // Setting for the 3D scene
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspectRatio, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//==============================================================================


//======================== Interativity ========================================
// Keyboard interaction
void keyboardInput(unsigned char key, int x, int y) {

}

void keyboardInputRelease(unsigned char key, int x, int y) {

}

// Arrows interaction
void specialKeys(int key, int x, int y) {

}

// Mouse interaction
void mouseInput(int button, int state, int x, int y) {

}
//==============================================================================


// Draws all the parts of the scene to be displayed on the screen (called on each event requiring the window to be repainted)
void display() {

}

// Supporting function to make certain objects on screen move/change (update coordinates with the passing of time_interval)
void update(int value) {

}

// Idle callback function (force OpenGL to redraw the current window)
void when_in_mainloop() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(235, 85);
    glutInitWindowSize(800, 500);
    glutCreateWindow("3D Modelling");
    glEnable(GL_DEPTH_TEST);

    // initTextures();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(when_in_mainloop);
    glutKeyboardFunc(keyboardInput);
    glutKeyboardUpFunc(keyboardInputRelease);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseInput);
    glutTimerFunc(0, update, 1);
    glutMainLoop();
    return 0;
}