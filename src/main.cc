#include "mountain.h"

#include <stdlib.h>
#include <GLUT/glut.h>

#include <iostream>

static Mountain m = Mountain(6, 7897);

/* Initialize OpenGL Graphics */
void initGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

static void display(void) {
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, -8.0f);
    glRotatef(40, 1, 0, 0);
    glRotatef(30, 0, 1, 0);
    glScalef(3, 3, 3);
    m.Render();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
  // Compute aspect ratio of the new window
  if (height == 0) height = 1;  // To prevent divide by 0
  GLfloat aspect = (GLfloat)width / (GLfloat)height;

  // Set the viewport to cover the new window
  glViewport(0, 0, width, height);

  // Set the aspect ratio of the clipping volume to match the viewport
  glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
  glLoadIdentity();             // Reset
  // Enable perspective projection with fovy, aspect, zNear and zFar
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Mountains");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMainLoop();
    return 0;
}
