#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "casa.h"

void rotateAllElements() {
    glRotatef(rotate, 0, 1, 0);
}

void drawSwing() {
    glPushMatrix();
    rotateAllElements();
    glScalef(0.05, 0.05, 0.05);
    glTranslatef(80, 1, 0);
    //    glRotatef(45, 1.0f, 0.0f, 0.0f);
    drawObject(balanco);
    glPopMatrix();
}

void drawFloor() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(0, 1, 0);
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
    rotateAllElements();
    glScalef(5, 5, 5);
    glTranslatef(0, 0, 0);
    drawObject(casa);
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    rotateAllElements();
    glScalef(0.03, 0.03, 0.03);
    glTranslatef(100, 200, 0);
    drawObject(carro);
    glPopMatrix();
}

void lighting() {
    float position[4] = {2.0f, 2.0f, 2.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //ativando luz ambiente global
    float global_ambient[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init() {
    GLfloat lightpos[] = {5.0f, 10.0f, 0.0f, 1.0f};
    glClearColor(0.5f, 0.5f, 0.0f, 1.0f);

    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    //    lighting();
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

    gluLookAt(cameraX, cameraY, cameraZ,
            0, 0, 0,
            0, 1, 0);

    drawHouse();
        drawSwing();
        drawFloor();
        drawCar();

    glFlush();
    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
    if (rotate > 360) {
        rotate -= 360;
    }
    if (cameraX < 5) {
        cameraX = 5;
        return;
    }
    if (cameraY < 0) {
        cameraY = 0;
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

    atexit(resetScene);
    init();

    casa = parseObjectFile("objetos/bg4_obj.obj");
    balanco = parseObjectFile("objetos/chair_swing/swingcushion.obj");
    carro = parseObjectFile("objetos/Bugatti-Veyron.obj");

    glutReshapeFunc(reshapeSwing);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);

    glutMainLoop();
    /*
     * atenuação radial
     * duas fontes de luz, ambiente e acima do solo
     * 
     */
    return 0;
}
