#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "vector"

#define checkImageWidth 64
#define checkImageHeight 64

using namespace std;

// Player's car animation variables
GLfloat carX = 0.0f;
GLfloat carY = 0.0f;
GLfloat carZ = -0.0f;
GLfloat carTurnAngle = 0.0f;
const GLfloat MAX_TURN_ANGLE = 5.0f;
const GLfloat MAX_CAR_X = 4.0f;
bool turningRight = false;
bool turningLeft = false;
GLfloat carSpeed = 0.0f;
GLfloat wheelRotationAngle = 0.0f;
GLint numSpeedUp = 0;

// Camera control
GLfloat camTurn = 0;

// NPC cars animation variables
GLfloat carNPCcoorZ = 0.0f;
GLfloat carNPCspeed = 0.1f;

// Texture variables
vector<GLubyte*>p;
GLuint textures[19];
GLint imagewidth0, imageheight0, pixellength0,
imagewidth1, imageheight1, pixellength1,
imagewidth2, imageheight2, pixellength2,
imagewidth3, imageheight3, pixellength3,
imagewidth4, imageheight4, pixellength4,
imagewidth5, imageheight5, pixellength5,
imagewidth6, imageheight6, pixellength6,
imagewidth7, imageheight7, pixellength7,
imagewidth8, imageheight8, pixellength8,
imagewidth9, imageheight9, pixellength9,
imagewidth10, imageheight10, pixellength10,
imagewidth11, imageheight11, pixellength11,
imagewidth12, imageheight12, pixellength12,
imagewidth13, imageheight13, pixellength13,
imagewidth14, imageheight14, pixellength14,
imagewidth15, imageheight15, pixellength15,
imagewidth16, imageheight16, pixellength16,
imagewidth17, imageheight17, pixellength17;
GLubyte checkImage[checkImageWidth][checkImageHeight][3];


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
//================================================================================


//======================= Texture mapping ========================================
void ReadImage(const char path[256], GLint& imagewidth, GLint& imageheight, GLint& pixellength) {
    // Reading bitmap images
    GLubyte* pixeldata;
    FILE* pfile;
    fopen_s(&pfile, path, "rb");
    if (pfile == 0) exit(0);

    fseek(pfile, 0x0012, SEEK_SET);
    fread(&imagewidth, sizeof(imagewidth), 1, pfile);
    fread(&imageheight, sizeof(imageheight), 1, pfile);

    pixellength = imagewidth * 3;
    while (pixellength % 4 != 0)pixellength++;
    pixellength *= imageheight;

    pixeldata = (GLubyte*)malloc(pixellength);
    if (pixeldata == 0) exit(0);

    fseek(pfile, 54, SEEK_SET);
    fread(pixeldata, pixellength, 1, pfile);
    p.push_back(pixeldata);

    fclose(pfile);
}

void setupTexture(GLuint textureID, GLubyte* data, GLint width, GLint height) {
    // Settings and parameters for texturing
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void initTextures(void) { // Texture initialization 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    glEnable(GL_TEXTURE_2D);

    ReadImage("grass.bmp", imagewidth0, imageheight0, pixellength0);
    ReadImage("bark.bmp", imagewidth1, imageheight1, pixellength1);
    ReadImage("road.bmp", imagewidth2, imageheight2, pixellength2);
    ReadImage("sand.bmp", imagewidth3, imageheight3, pixellength3);
    ReadImage("foliage.bmp", imagewidth4, imageheight4, pixellength4);
    ReadImage("crate.bmp", imagewidth5, imageheight5, pixellength5);
    ReadImage("barrier.bmp", imagewidth6, imageheight6, pixellength6);
    ReadImage("flagstone.bmp", imagewidth7, imageheight7, pixellength7);
    ReadImage("building.bmp", imagewidth8, imageheight8, pixellength8);
    ReadImage("building1.bmp", imagewidth9, imageheight9, pixellength9);
    ReadImage("building2.bmp", imagewidth10, imageheight10, pixellength10);
    ReadImage("building3.bmp", imagewidth11, imageheight11, pixellength11);
    ReadImage("cones.bmp", imagewidth12, imageheight12, pixellength12);
    ReadImage("light.bmp", imagewidth13, imageheight13, pixellength13);
    ReadImage("window.bmp", imagewidth14, imageheight14, pixellength14);
    ReadImage("metal.bmp", imagewidth15, imageheight15, pixellength15);
    ReadImage("license.bmp", imagewidth16, imageheight16, pixellength16);
    ReadImage("aluminum.bmp", imagewidth17, imageheight17, pixellength17);
    // makeCheckImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(19, &textures[0]);

    setupTexture(textures[0], p[0], imagewidth0, imageheight0);
    setupTexture(textures[1], p[1], imagewidth1, imageheight1);
    setupTexture(textures[2], p[2], imagewidth2, imageheight2);
    setupTexture(textures[3], p[3], imagewidth3, imageheight3);
    setupTexture(textures[4], p[4], imagewidth4, imageheight4);
    setupTexture(textures[5], p[5], imagewidth5, imageheight5);
    setupTexture(textures[6], p[6], imagewidth6, imageheight6);
    setupTexture(textures[7], p[7], imagewidth7, imageheight7);
    setupTexture(textures[8], p[8], imagewidth8, imageheight8);
    setupTexture(textures[9], p[9], imagewidth9, imageheight9);
    setupTexture(textures[10], p[10], imagewidth10, imageheight10);
    setupTexture(textures[11], p[11], imagewidth11, imageheight11);
    setupTexture(textures[12], p[12], imagewidth12, imageheight12);
    setupTexture(textures[13], p[13], imagewidth13, imageheight13);
    setupTexture(textures[14], p[14], imagewidth14, imageheight14);
    setupTexture(textures[15], p[15], imagewidth15, imageheight15);
    setupTexture(textures[16], p[16], imagewidth16, imageheight16);
    setupTexture(textures[17], p[17], imagewidth17, imageheight17);
    setupTexture(textures[18], (GLubyte*)checkImage, checkImageWidth, checkImageHeight);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
//==============================================================================


//=========================== Lighting and Materials =============================
void setMaterial(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

void setShinyMaterial() {
    GLfloat ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat diffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat shininess = 90.0f;

    setMaterial(ambient, diffuse, specular, shininess);
}

void setMatteMaterial() {
    GLfloat ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat shininess = 0.0f;

    setMaterial(ambient, diffuse, specular, shininess);
}
//================================================================================


//================ Generic functions to texture 3D shapes ========================
void drawTexturedCylinder(GLuint textureID, GLfloat baseRadius, GLfloat topRadius,
    GLfloat height, GLint slices, GLint stacks) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Draw the side surface
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);

    // Draw the bottom base
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, 0.0f, 0.0f); // Center point
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = 2.0f * 3.14 * (GLfloat)i / (GLfloat)slices;
        GLfloat x = baseRadius * cosf(angle);
        GLfloat y = baseRadius * sinf(angle);
        glTexCoord2f(x * 0.5f / baseRadius + 0.5f, y * 0.5f / baseRadius + 0.5f);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    // Draw top base
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, 0.0f, height); // Center point
    for (int i = 0; i <= slices; i++) {
        GLfloat angle = 2.0f * 3.14 * (GLfloat)i / (GLfloat)slices;
        GLfloat x = topRadius * cosf(angle);
        GLfloat y = topRadius * sinf(angle);
        glTexCoord2f(x * 0.5f / topRadius + 0.5f, y * 0.5f / topRadius + 0.5f);
        glVertex3f(x, y, height);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadric);
}

void drawTexturedSphere(GLuint textureID, GLfloat radius, GLint slices, GLint stacks) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    gluSphere(quadric, radius, slices, stacks);
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quadric);
}

void drawTexturedCube(GLuint textureID, GLfloat size) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, -size, -size);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, size, -size);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(size, -size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, -size, size);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, size, size);
    glTexCoord2f(0.0, 1.0); glVertex3f(size, size, -size);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(-size, -size, size);
    glTexCoord2f(1.0, 1.0); glVertex3f(-size, size, size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, size, -size);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, size, -size);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, size, -size);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, size, size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, size, size);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0); glVertex3f(-size, -size, size);
    glTexCoord2f(1.0, 0.0); glVertex3f(size, -size, size);
    glTexCoord2f(1.0, 1.0); glVertex3f(size, -size, -size);
    glTexCoord2f(0.0, 1.0); glVertex3f(-size, -size, -size);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
//================================================================================


//=============== Functions to draw various parts of the scene ===================
//______________________________ Main surface ____________________________________
void drawGround() { // Drawing tile by tile for the texture to map without pixelation
    setMatteMaterial();
    for (int z = -500; z < 1100; z += 20) {
        for (int x = -100; x < 100; x += 20) {
            glPushMatrix();
            glTranslatef((GLfloat)x, -3.0f, (GLfloat)-1000.0f + z);
            glScalef(1.0f, 0.01f, 1.0f);
            drawTexturedCube(textures[0], 10.0f);
            glPopMatrix();
        }
    }
}

void drawRoad() { // Drawing tile by tile to avoid pixelation
    setMatteMaterial();

    for (GLfloat z = -1500.0f; z < 100.0f; z += 12.0f) {
        glPushMatrix();
        glTranslatef(0.0f, -8.4f, z);
        drawTexturedCube(textures[2], 6.0f);
        glPopMatrix();
    }
}

void drawSidewalk() { // Drawing tile by tile to avoid pixelation
    setMatteMaterial();

    for (int i = -500; i < 800; i++) {
        GLfloat zPosition = -1000.0f + (i * 5.0f);

        glPushMatrix(); // Right side
        glTranslatef(8.15f, -4.7f, zPosition);
        drawTexturedCube(textures[7], 2.5f);
        glPopMatrix();

        glPushMatrix(); // Left side
        glTranslatef(-8.15f, -4.7f, zPosition);
        drawTexturedCube(textures[7], 2.5f);
        glPopMatrix();
    }
}
//________________________________________________________________________________


//___________________________________ Cars _______________________________________
void drawWheel(GLfloat x, GLfloat y, GLfloat z) {
    glDisable(GL_LIGHTING);

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(wheelRotationAngle, 0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.15, 0.17, 10, 50);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawCarLight(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.15f, 0.1f, 0.1f);
    drawTexturedCube(textures[13], 1.0f);
    glPopMatrix();
}

void drawCar() {
    setShinyMaterial();

    glPushMatrix();
    glRotatef(carTurnAngle, 0.0f, -1.0f, 0.0f);

    // Body
    glPushMatrix();
    glTranslatef(0.0f, -0.7f, -3.4f);
    glScalef(1.3f, 0.6f, 2.2f);
    drawTexturedCube(textures[15], 0.5f);
    glPopMatrix();

    // Roof
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, -3.6f);
    glScalef(1.29f, 0.55f, 1.2f);
    drawTexturedCube(textures[15], 0.5f);
    glPopMatrix();

    // Window
    glPushMatrix();  // Back
    glTranslatef(0.0f, -0.1f, -3.3f);
    glScalef(0.55f, 0.2f, 0.35f);
    drawTexturedCube(textures[14], 1.0f);
    glPopMatrix();

    glPushMatrix();  // Sides
    glTranslatef(0.0f, -0.1f, -3.6f);
    glScalef(0.66f, 0.2f, 0.3f);
    drawTexturedCube(textures[14], 1.0f);
    glPopMatrix();

    // Lights
    drawCarLight(0.49f, -0.65f, -2.39f);  // Right
    drawCarLight(-0.49f, -0.65f, -2.39f); // Left

    // License Plate
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, -2.3f);
    glScalef(0.5f, 0.25f, 0.1f);
    drawTexturedCube(textures[16], 0.5f);
    glPopMatrix();

    // Bumper
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.0f, -0.95f, -3.4f);
    glScalef(1.31f, 0.1f, 2.4f);
    glutSolidCube(1);
    glColor3f(0, 0, 0);
    glutWireCube(1);
    glPopMatrix();

    // Tires
    drawWheel(-0.61f, -0.95f, -2.8f); // Rear left
    drawWheel(-0.61f, -0.95f, -3.9f); // Front left
    drawWheel(0.61f, -0.95f, -2.8f);  // Rear right
    drawWheel(0.61f, -0.95f, -3.9f);  // Front right

    glPopMatrix();
}

void drawCarNPClight(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(0.2f, 0.15f, 0.2f);
    drawTexturedSphere(textures[13], 1, 32, 10);
    glPopMatrix();
}

void drawCarNPC(GLfloat x, GLfloat y, GLfloat z) {
    setShinyMaterial();

    // Body
    glPushMatrix();
    glTranslatef(x + 0.0f, y - 0.7f, z - 3.4f);
    glScalef(0.8f, 0.4f, 1.2f);
    drawTexturedCylinder(textures[17], 1, 1, 3, 32, 1);
    glPopMatrix();

    // Roof
    glPushMatrix();
    glTranslatef(x + 0.0f, y - 0.2f, z - 1.5);
    glScalef(0.7f, 0.55f, 1.5f);
    drawTexturedSphere(textures[15], 1, 32, 10);
    glPopMatrix();

    // Lights
    drawCarNPClight(x + 0.5f, y - 0.69f, z + 0.2f); // Right
    drawCarNPClight(x - 0.5f, y - 0.69f, z + 0.2f); // Left

    // Tires
    drawWheel(x - 0.72f, y - 0.95f, z - 2.8f); // Rear left
    drawWheel(x - 0.72f, y - 0.95f, z - 0.2f); // Front left
    drawWheel(x + 0.72f, y - 0.95f, z - 2.8f); // Rear right
    drawWheel(x + 0.72f, y - 0.95f, z - 0.2f); // Front right
}
//________________________________________________________________________________


// Draws all the parts of the scene to be displayed on the screen (called on each event requiring the window to be repainted)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camTurn, 0.1, carZ + 5.0, 0.0, 0.0, carZ, 0.0, 1.0, 0.0);

    //---------------------- Environment ------------------------------
    drawGround();
    drawRoad();
    drawSidewalk();
    //-----------------------------------------------------------------

    //------------------------ Obstacles ------------------------------
    glPushMatrix();
    glTranslatef(0, 0, carNPCcoorZ);
    drawCarNPC(-2, -1.15, -520);
    drawCarNPC(3, -1.15, -580);
    glPopMatrix();
    //-----------------------------------------------------------------

    //--------------------- Player's car ------------------------------
    glPushMatrix();
    glTranslatef(carX, carY + -1.15f, carZ + 1.0f);
    drawCar();
    glPopMatrix();
    //-----------------------------------------------------------------

    glFlush();
    glutSwapBuffers();
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

    initTextures();
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