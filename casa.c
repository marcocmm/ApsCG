#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "casa.h"

void rotateAllElements() {
    glRotatef(rotate, 0, 1, 0);
}

void drawFloor() {
    glPushMatrix();
    rotateAllElements();
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(-20, -0.5, 20);
    glVertex3f(20, -0.5, 20);
    glVertex3f(20, -0.5, -20);
    glVertex3f(-20, -0.5, -20);
    glEnd();
    glPopMatrix();
}

void drawHouse() {
    rotateAllElements();
    drawObject(casa);
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ,
            0, 0, 0,
            0, 1, 0);

    drawHouse();
    drawFloor();
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
    if (cameraX > 20) {
        cameraX = 20;
        return;
    }
    if (cameraY > 20) {
        cameraY = 20;
        return;
    }
    if (cameraZ > 20) {
        cameraZ = 20;
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
            cameraX += 0.2;
            cameraY += 0.2;
            cameraZ += 0.2;
            break;
        case GLUT_KEY_DOWN:
            cameraX -= 0.2;
            cameraY -= 0.2;
            cameraZ -= 0.2;
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
            cameraY -= 0.2;
            break;
        case GLUT_KEY_F2:
            cameraY += 0.2;
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

    cameraX = 10;
    cameraY = 10;
    cameraZ = 10;
    rotate = 0;

    atexit(resetScene);
    init();
    casa = parseObjectFile("casa.obj");

    glutReshapeFunc(reshape);
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
