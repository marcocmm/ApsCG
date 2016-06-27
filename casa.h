#pragma once

#include "glm.h"
#include "object.h"

GLdouble cameraX = 50;
GLdouble cameraY = 50;
GLdouble cameraZ = 50;
GLdouble focoX = 0;
GLdouble focoY = 0;
GLdouble focoZ = 0;

GLint rotateScene = 0;

GLfloat translatefCar_x = -10;
GLfloat rotateCar = 0;

GLfloat rotateSun = 10;
GLfloat corCeu = 0;

GLint isDayLight;

GLMmodel *casa;
GLMmodel *balanco;
GLMmodel *carro;
GLMmodel *post;
GLMmodel *fence;