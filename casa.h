#pragma once

#include "glm.h"

GLdouble cameraX, cameraY, cameraZ;
GLint rotate;
//Object* casa;
//Object* balanco;
//Object* carro;
//Object* post;
float luz;
int translatefCar_x = 200;
int rotateCar_z = 90;
int y = 1;

int translatefSun_x = 20;
int translatefSun_y = -10;
int translatefSun_z = -60;
int inverteSun = 0;
float attenuationSun = 0.5;
GLMmodel *casa;
GLMmodel *balanco;
GLMmodel *carro;
GLMmodel *post;

