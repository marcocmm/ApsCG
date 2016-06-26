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

    GLfloat positionLight0[] = {50.0f, 50.0f, 50.0f};
    GLfloat ambientLight0[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight0[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specularLight0[] = {0.4f, 0.4f, 0.4f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);

    glEnable(GL_LIGHT0);

    GLfloat positionLight1[] = {100, 10, 30};
    GLfloat ambientLight1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight1[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specularLight1[] = {0.4f, 0.4f, 0.4f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, positionLight1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.6f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.3f);

    glEnable(GL_LIGHT1);

    GLfloat ambientSun[4] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientSun);

    glEnable(GL_LIGHT2);

    GLfloat global_ambient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
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
    //    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, attenuationSun);
    //    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, attenuationSun);
    //    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, attenuationSun);
    rotateSun += 1;
    if (rotateSun > 360) {
        rotateSun -= 360;
    }
    if (rotateSun == 0) {
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT_MODEL_AMBIENT);
    } else if (rotateSun == 90) {
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT_MODEL_AMBIENT);
    }
    //    if (translatefSun_y > 100) {
    //        amanhecendo = 0;
    //        anoitecendo = 1;
    //    } else if (translatefSun_y < 0) {
    //        anoitecendo = 0;
    //        noite = 1;
    //    } else if (translatefSun_y < -70) {
    //        amanhecendo = 1;
    //        anoitecendo = 0;
    //    }

    //    if (noite) {
    //        translatefSun_z += 0.1;
    //        translatefSun_y += 0.2 * value;
    //        translatefSun_x += 0.1;
    //    } else if (amanhecendo) {
    //        translatefSun_z += 0.1;
    //        translatefSun_y += 0.1;
    //        translatefSun_x += 0.1;
    //    } else if (anoitecendo) {
    //        translatefSun_z += 0.1;
    //        translatefSun_y -= 0.1;
    //        translatefSun_x += 0.1;
    //    }
    //            attenuationSun += 0.2;
    //    if (isDayLight) {
    //        if (translatefSun_y > -3) {
    //            translatefSun_y -= 1;
    //            translatefSun_z += 1.5;
    //            translatefSun_x -= 1.1;
    //            attenuationSun -= 0.2;
    //        } else {
    //            isDayLight = 0;
    //            translatefSun_x = 20;
    //            translatefSun_y = -10;
    //            translatefSun_z = -60;
    //            attenuationSun = 0.5;
    //            glDisable(GL_LIGHT2);
    //            glDisable(GL_LIGHT_MODEL_AMBIENT);
    //        }
    //    }
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
