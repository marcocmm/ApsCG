#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "casa.h"

void rotateAllElements() {
    glRotatef(rotate, 0, 1, 0);
}

GLfloat getPercentageOfComponent(GLint component) {
    return component / 255.0;
}

void drawSwing() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(getPercentageOfComponent(120), getPercentageOfComponent(68), getPercentageOfComponent(33));
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(80, 1, 30);
    //    glRotatef(45, 1.0f, 0.0f, 0.0f);
    drawObject(balanco);
    glPopMatrix();
}

void drawFloor() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0, 1, 0);
    glVertex3f(-50, 0, 50);
    glVertex3f(50, 0, 50);
    glVertex3f(50, 0, -50);
    glVertex3f(-50, 0, -50);
    glEnd();
    glPopMatrix();
}

void drawHouse() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(1.0f, 1.0f, 1.0f);
    glScalef(2.5, 2.5, 2.5);
    glTranslatef(0, -1, -7);
    drawObject(casa);
    glPopMatrix();
}

void drawPost() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(0.0f, 0.3f, 0.3f);
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(100, 0, 30);
    drawObject(post);
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(3.0f, 0.0f, 0.1f);
    //        glRotated(0, 0, 1, 0);
    glRotated(rotateCar_z, 0, y, 0);
    glScalef(0.018, 0.018, 0.018);
    glTranslatef(translatefCar_x, 200, -1000);
    drawObject(carro);
    glPopMatrix();
}

void init() {
    glClearColor(0.6f, 0.70980392156f, 0.81960784313f, 0.0f);

    glEnable(GL_LIGHTING);

    GLfloat ambientGlobal[4] = {0.0f, 0.6f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientGlobal);

    GLfloat positionLight0[] = {0.0f, 20.0f, 0.0f};
    GLfloat ambientLight0[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuseLight0[] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat specularLight0[] = {1.0f, 0.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);

    glEnable(GL_LIGHT0);

    GLfloat positionLight1[] = {100, 10, 30};
    GLfloat ambientLight1[] = {1.0f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuseLight1[] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat specularLight1[] = {1.0f, 0.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, positionLight1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

    glEnable(GL_LIGHT1);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
////    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
////    glClear(GL_DEPTH_BUFFER_BIT);
////    glEnable(GL_DEPTH_TEST);

    //    lighting();
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

void resetScene() {
    resetModel(casa);
    resetModel(balanco);
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

    luz += 0.1;
    if (luz > 1) {
        luz = 0;
    }
    glClearColor(luz, luz, luz, 1.0f);

    gluLookAt(cameraX, cameraY, cameraZ,
            0, 0, 0,
            0, 1, 0);

    drawHouse();
    drawSwing();
    drawFloor();
    drawCar();
    drawPost();

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

void keyboard(int key, int x, int y) {
    if (rotate > 360) {
        rotate -= 360;
    }
    if (cameraX < 5) {
        cameraX = 5;
        return;
    }
    if (cameraY < 5) {
        cameraY = 5;
        return;
    }
    if (cameraZ < 5) {
        cameraZ = 5;
        return;
    }
    if (cameraX > 100) {
        cameraX = 100;
        return;
    }
    if (cameraY > 100) {
        cameraY = 100;
        return;
    }
    if (cameraZ > 100) {
        cameraZ = 100;
        return;
    }
    switch (key) {
        case GLUT_KEY_LEFT:
            rotate += 1;
            break;
        case GLUT_KEY_RIGHT:
            rotate -= 1;
            break;
        case GLUT_KEY_UP:
            cameraX -= 1;
            cameraY -= 1;
            cameraZ -= 1;
            break;
        case GLUT_KEY_DOWN:
            cameraX += 1;
            cameraY += 1;
            cameraZ += 1;
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
            cameraY -= 1;
            break;
        case GLUT_KEY_F2:
            cameraY += 1;
            break;
        case GLUT_DOWN:
            cameraZ -= 1;
            break;
        case GLUT_KEY_F8:
            glDisable(GL_LIGHT1);
            break;
        case GLUT_KEY_F9:
            glEnable(GL_LIGHT1);
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Casa Numero 0");

    cameraX = 50;
    cameraY = 50;
    cameraZ = 50;
    rotate = 0;
    luz = 0;

    atexit(resetScene);
    init();

    balanco = parseObjectFile("objetos/chair_swing/swingcushion.obj");
    casa = parseObjectFile("objetos/bg4_obj.obj");
    carro = parseObjectFile("objetos/Bugatti-Veyron.obj");
    post = parseObjectFile("objetos/post.obj");

    glutReshapeFunc(reshapeSwing);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(moveCar);
//    glutKeyboardFunc(moveCarLR);

    glutMainLoop();
    /*
     * atenuação radial
     * duas fontes de luz, ambiente e acima do solo
     * 
     */
    return 0;
}
