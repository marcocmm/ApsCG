#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "casa.h"
#include "glm.h"
#include "glmint.h"

void alignScene() {
    glRotatef(rotateScene, 0, 1, 0);
}

GLfloat getPercentageOfComponent(GLint component) {
    return component / 255.0;
}

void drawSwing() {
    glPushMatrix();
    alignScene();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(80, 1, 30);
    glmDraw(balanco, GLM_FLAT);
    glPopMatrix();
}

void drawFloor() {
    glPushMatrix();
    alignScene();

    GLfloat diffuse[4] = {0.65f, 0.65f, 0.0f, 1.0f};
    GLfloat specular[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat shininess = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glColor3f(0.0f, 0.3f, 0.0f);

    glBegin(GL_QUADS);
    glVertex3f(-50, 0, 50);
    glVertex3f(50, 0, 50);
    glVertex3f(50, 0, -50);
    glVertex3f(-50, 0, -50);
    glEnd();
    glPopMatrix();
}

void drawHouse() {
    glPushMatrix();
    alignScene();
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(0, 0, 0);
    glmDraw(casa, GLM_COLOR);
    glPopMatrix();
}

void drawPost() {
    glPushMatrix();
    alignScene();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(100, 0, 30);
    glmDraw(post, GLM_COLOR);
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    alignScene();
    glRotated(rotateCar_z, 0, 1, 0);
    glTranslatef(translatefCar_x, 0, 10);
    glmDraw(carro, GLM_COLOR);
    glPopMatrix();
}

void drawSun() {
    glPushMatrix();
    alignScene();
    glColor3f(getPercentageOfComponent(243), getPercentageOfComponent(159), getPercentageOfComponent(24));
    glRotatef(rotateSun, 1, 0, 1);
    glTranslatef(-70, -70, -70);
    glutSolidSphere(20, 40, 40);
    glPopMatrix();
}

void drawFence() {
    int i;
    for (i = -4; i < 6; i += 3) {
        glPushMatrix();
        alignScene();
        glScalef(10, 10, 10);
        glTranslatef(i, 0, 5);
        glmDraw(fence, GLM_COLOR);
        glPopMatrix();
    }
    for (i = -4; i < 6; i += 3) {
        glPushMatrix();
        alignScene();
        glScalef(10, 10, 10);
        glTranslatef(i, 0, -5);
        glmDraw(fence, GLM_COLOR);
        glPopMatrix();
    }
    for (i = -5; i < 6; i += 3) {
        glPushMatrix();
        alignScene();
        glScalef(10, 10, 10);
        glTranslatef(5, 0, i);
        glRotatef(90, 0, 1, 0);
        glmDraw(fence, GLM_COLOR);
        glPopMatrix();
    }
    for (i = -5; i < 6; i += 3) {
        glPushMatrix();
        alignScene();
        glScalef(10, 10, 10);
        glTranslatef(-5, 0, i);
        glRotatef(90, 0, 1, 0);
        glmDraw(fence, GLM_COLOR);
        glPopMatrix();
    }
}

void init() {
    glClearColor(0.6f, 0.70980392156f, 0.81960784313f, 0.0f);

    glEnable(GL_LIGHTING);

    GLfloat positionHouse[] = {0, 20, 0};
    GLfloat ambientHouse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseHouse[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat specularHouse[] = {0.1f, 0.1f, 0.1f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, positionHouse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientHouse);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseHouse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularHouse);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.15f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.1f);

    GLfloat positionPost[] = {10, 10, 30};
    GLfloat ambientPost[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffusePost[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat specularPost[] = {0.1f, 0.1f, 0.1f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, positionPost);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientPost);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffusePost);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularPost);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.6f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.2f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.3f);

    GLfloat positionSun[] = {0, 30, 0};
    GLfloat ambientSun[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat diffuseSun[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat specularSun[] = {0.5f, 0.5f, 0.5f, 1.0f};

    glLightfv(GL_LIGHT2, GL_POSITION, positionSun);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientSun);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseSun);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularSun);

    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.2f);

    GLfloat global_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
}

void resetScene() {
    resetModel(NULL);
    resetModel(NULL);
}

void reshape(int w, int h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w / (GLdouble) h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void reshapeSwing(int w, int h) {
    if (h == 0)
        h = 1;

    glViewport(0, 10, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, w / (GLdouble) h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //    if (isDayLight) {
    //        luz += 0.007;
    //    } else {
    //        luz -= 0.007;
    //    }
    //
    //    glClearColor(0, luz, luz, 1.0f);

    gluLookAt(cameraX, cameraY, cameraZ,
            focoX, focoY, focoZ,
            0, 1, 0);

    drawFloor();
    drawHouse();
    drawSwing();
    //    drawCar();
    drawPost();
    drawSun();
    //    drawFence();
    glutSwapBuffers();
}

void moveCar(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 'w':
            if (translatefCar_x > -1000) {
                translatefCar_x -= 15;
            }
            break;
        case 's':
            if (translatefCar_x < 200) {
                translatefCar_x += 15;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void moveCarLR(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 'a':
            rotateCar_z -= 10;
            break;
        case 'd':
            rotateCar_z += 10;
            break;
    }
}

void moveFocoCamera(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case '6':
            if (focoX < 50) {
                focoX += 1;
            }
            break;
        case '4':
            if (focoX > -50) {
                focoX -= 1;
            }
            break;
        case '2':
            if (focoZ < 50) {
                focoZ += 1;
            }
            break;
        case '8':
            if (focoZ > -50) {
                focoZ -= 1;
            }
            break;
        case '5':
            focoX = 0;
            focoZ = 0;
            break;
    }
}

void keyboardLetras(unsigned char key, int xmouse, int ymouse) {
    moveCar(key, xmouse, ymouse);
    moveCarLR(key, xmouse, ymouse);
    moveFocoCamera(key, xmouse, ymouse);
}

void timerSun(int value) {
    rotateSun += 1;
    if (rotateSun > 360) {
        rotateSun -= 360;
    }
    if (rotateSun == 270) {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT_MODEL_AMBIENT);
    } else if (rotateSun == 80) {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT_MODEL_AMBIENT);
    }
    glutPostRedisplay();
    glutTimerFunc(10, timerSun, value + 1);
}

void keyboard(int key, int x, int y) {
    if (rotateScene > 360) {
        rotateScene -= 360;
    }
    switch (key) {
        case GLUT_KEY_LEFT:
            rotateScene += 1;
            break;
        case GLUT_KEY_RIGHT:
            rotateScene -= 1;
            break;
        case GLUT_KEY_UP:
            if (cameraX > 5) {
                cameraX -= 1;
            }
            if (cameraY > 5) {
                cameraY -= 1;
            }
            if (cameraZ > 5) {
                cameraZ -= 1;
            }
            break;
        case GLUT_KEY_DOWN:
            if (cameraX < 100) {
                cameraX += 1;
            }
            if (cameraY < 100) {
                cameraY += 1;
            }
            if (cameraZ < 100) {
                cameraZ += 1;
            }
            break;
        case GLUT_KEY_HOME:
            cameraX = 10;
            cameraY = 10;
            cameraZ = 10;
            break;
        case GLUT_KEY_END:
            cameraX = 30;
            cameraY = 30;
            cameraZ = 30;
            break;
        case GLUT_KEY_F1:
            if (cameraY > 5) {
                cameraY -= 1;
            }
            break;
        case GLUT_KEY_F2:
            if (cameraY < 100) {
                cameraY += 1;
            }
            break;
        case GLUT_KEY_F8:
            glDisable(GL_LIGHT_MODEL_AMBIENT);
            break;
        case GLUT_KEY_F9:
            glEnable(GL_LIGHT_MODEL_AMBIENT);
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    casa = glmReadOBJ("objects/Cyprys_House.obj");
    balanco = glmReadOBJ("objects/swingcushion.obj");
    post = glmReadOBJ("objects/black lamp spotIVI 01.obj");
    carro = glmReadOBJ("objects/koenigsegg.obj");
    fence = glmReadOBJ("objects/Forged_fence.obj");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Casa Numero 0");

    atexit(resetScene);
    init();

    glutReshapeFunc(reshapeSwing);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyboardLetras);
    glutTimerFunc(10, timerSun, 1);

    glutMainLoop();
    return 0;
}
