#include <GL/glut.h>
#include "casa.h"

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Casa Numero 0");

    obsX = 5;
    obsY = 5;
    obsZ = 5;
    
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    loadObj("casa.obj");
    glutMainLoop();
    return 0;
}
