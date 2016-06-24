#pragma once

#include <GL/gl.h>

GLuint glGenList;
GLfloat rotate;
GLdouble obsX, obsY, obsZ;

void SpecialKeys(int key, int x, int y);

/**
 * Carrega objeto.
 * @param fname
 */
void loadObj(char *fname);
void reshape(int w, int h);
void drawHouse();
void display();