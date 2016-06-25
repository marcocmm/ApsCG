#pragma once

#include "glm.h"

GLdouble cameraX = 50;
GLdouble cameraY = 50;
GLdouble cameraZ = 50;
GLdouble focoX = 0;
GLdouble focoY = 0;
GLdouble focoZ = 0;

GLint rotateScene = 0;
GLfloat luz = 0;

GLint translatefCar_x = 0;
GLint rotateCar_z = 0;
GLint y = 1;

GLint translatefSun_x = 20;
GLint translatefSun_y = -10;
GLint translatefSun_z = -60;
GLint isDayLight = 0;
GLfloat attenuationSun = 0.5;

GLMmodel *casa;
GLMmodel *balanco;
GLMmodel *carro;
GLMmodel *post;