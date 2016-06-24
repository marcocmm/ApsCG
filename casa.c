#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "casa.h"

void SpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if ((((obsZ > 0 && obsZ <= 5) || (obsZ <= -5 && obsZ > -7)) && obsX > 0) || (((obsZ >= -5 && obsZ < 0) || (obsZ >= 5 && obsZ < 7)) && obsX <= 0)) {
                obsZ += 0.1;
            } else {
                obsZ -= 0.1;
            }
            if ((obsZ > 0 && obsX >= 0) || (obsZ < 0 && obsX <= 0)) {
                obsX += 0.1;
            }else {
                obsX -= 0.1;
            }
            break;
        case GLUT_KEY_RIGHT:
            obsX += 0.2;
            if (obsX > -15) {
                obsZ -= 0.2;
            } else {
                obsZ -= 0.2;
            }
            break;
        case GLUT_KEY_UP:
            obsY += 0.2;
            break;
        case GLUT_KEY_DOWN:
            obsY -= 0.2;
            break;
        case GLUT_KEY_HOME:
            obsZ += 0.2;
            break;
        case GLUT_KEY_END:
            obsZ -= 0.2;
            break;
    }
    glutPostRedisplay();
}

struct {
    int a;
} Face;

struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertice;

void loadObj(char *fname) {
    FILE *fp;
    int read;
    GLfloat x, y, z;
    GLint f1, f2, f3, f4;
    glGenList = glGenLists(1);
    char* line = (char*) calloc(128, sizeof (char));
    fp = fopen(fname, "r");
    if (!fp) {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(glGenList, GL_COMPILE);
    glPushMatrix();
    {
        glBegin(GL_POINTS);
        while (!(feof(fp))) {
            //            read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
            read = fscanf(fp, "%s", line);
            printf("%s\n", line);
            if (!strcmp(line, "v")) {
                read = fscanf(fp, "%f %f %f", &x, &y, &z);
                glVertex3f(x, y, z);
            } else if (!strcmp(line, "vt")) {
                printf("vt");
            } else if (!strcmp(line, "f")) {
                read = fscanf(fp, "%d %d, %d, %d", &f1, &f2, &f3, &f4);
                //                read = fscanf(fp, "%d/%d %d/%d %d/%d %d/%d", &f1, &f2, &f3, &f4);
                //                printf("%d/%d\n", f1, f2);
                if (read == 3) {
                    glNormal3i(f1, f2, f3);
                }
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
    //    glOrtho(0, w, h, 0, 0, 50);
    glMatrixMode(GL_MODELVIEW);
}

void drawHouse() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(1.0, 0.23, 0.27);
    glScalef(0.8, 0.8, 0.8);
    //    glRotatef(rotate, 0, 1, 0);
    glCallList(glGenList);
    glPopMatrix();
    rotate = rotate + 0.3;
    if (rotate > 360) {
        rotate = rotate - 360;
    }
}

void drawFloor() {
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(-5, -0.5, 5);
    glVertex3f(5, -0.5, 5);
    glVertex3f(5, -0.5, -5);
    glVertex3f(-5, -0.5, -5);
    glEnd();
    glCallList(glGenList);
    glPopMatrix();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(obsX, obsY, obsZ,
            0, 0, 0,
            0, 1, 0);
    drawHouse();
    drawFloor();
    glutSwapBuffers();
}