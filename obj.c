#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obj.h"

void resetModel(Object *object) {
    int i;

    if (object) {
        if (object->vertices) {
            free(object->vertices);
            object->vertices = NULL;
        }

        if (object->texCoords) {
            free(object->texCoords);
            object->texCoords = NULL;
        }

        if (object->normais) {
            free(object->normais);
            object->normais = NULL;
        }

        if (object->faces) {
            for (i = 0; i < object->quantidadeFaces; ++i) {
                if (object->faces[i].vertices)
                    free(object->faces[i].vertices);

                if (object->faces[i].texturas)
                    free(object->faces[i].texturas);

                if (object->faces[i].normais)
                    free(object->faces[i].normais);
            }

            free(object->faces);
            object->faces = NULL;
        }
    }
}

int createObject(Object *object) {
    if (object->quantidadeVertices) {
        object->vertices = (struct vertice *)
                malloc(sizeof (struct vertice) * object->quantidadeVertices);
        if (!object->vertices)
            return 0;
    }

    if (object->quantidadeTexturas) {
        object->texCoords = (struct textura *)
                malloc(sizeof (struct textura) * object->quantidadeTexturas);
        if (!object->texCoords)
            return 0;
    }

    if (object->quantidadeNormais) {
        object->normais = (struct normal *)
                malloc(sizeof (struct normal) * object->quantidadeNormais);
        if (!object->normais)
            return 0;
    }

    if (object->quantidadeFaces) {
        object->faces = (struct face *)
                calloc(object->quantidadeFaces, sizeof (struct face));
        if (!object->faces)
            return 0;
    }

    return 1;
}

int initializeObject(FILE *file, Object *object) {
    int v, t, n;
    char buf[256];

    while (!feof(file)) {
        /* Read whole line */
        fgets(buf, sizeof (buf), file);

        switch (buf[0]) {
            case 'v':
            {
                if (buf[1] == ' ') {
                    /* Vertex */
                    object->quantidadeVertices++;
                } else if (buf[1] == 't') {
                    /* Texture coords. */
                    object->quantidadeTexturas++;
                } else if (buf[1] == 'n') {
                    /* Normal vector */
                    object->quantidadeNormais++;
                } else {
                    printf("Warning: unknown token \"%s\"! (ignoring)\n", buf);
                }

                break;
            }

            case 'f':
            {
                /* Face */
                if (sscanf(buf + 2, "%d/%d/%d", &v, &n, &t) == 3) {
                    object->quantidadeFaces++;
                    object->possuiTextura = 1;
                    object->possuiNormais = 1;
                } else if (sscanf(buf + 2, "%d//%d", &v, &n) == 2) {
                    object->quantidadeFaces++;
                    object->possuiTextura = 0;
                    object->possuiNormais = 1;
                } else if (sscanf(buf + 2, "%d/%d", &v, &t) == 2) {
                    object->quantidadeFaces++;
                    object->possuiTextura = 1;
                    object->possuiNormais = 0;
                } else if (sscanf(buf + 2, "%d", &v) == 1) {
                    object->quantidadeFaces++;
                    object->possuiTextura = 0;
                    object->possuiNormais = 0;
                } else {
                    /* Should never be there or the model is very crappy */
                    fprintf(stderr, "Error: found face with no vertex!\n");
                }

                break;
            }

            case 'g':
            {
                /* Group */
                /*	fscanf (fp, "%s", buf); */
                break;
            }

            default:
                break;
        }
    }

    /* Check if informations are valid */
    if ((object->possuiTextura && !object->quantidadeTexturas) ||
            (object->possuiNormais && !object->quantidadeNormais)) {
        fprintf(stderr, "error: contradiction between collected info!\n");
        return 0;
    }

    if (!object->quantidadeVertices) {
        fprintf(stderr, "error: no vertex found!\n");
        return 0;
    }

    printf("first pass results: found\n");
    printf("   * %i vertices\n", object->quantidadeVertices);
    printf("   * %i texture coords.\n", object->quantidadeTexturas);
    printf("   * %i normal vectors\n", object->quantidadeNormais);
    printf("   * %i faces\n", object->quantidadeFaces);
    printf("   * has texture coords.: %s\n", object->possuiTextura ? "yes" : "no");
    printf("   * has normals: %s\n", object->possuiNormais ? "yes" : "no");

    return 1;
}

int populateObject(FILE *file, Object *object) {
    struct vertice *pvert = object->vertices;
    struct textura *puvw = object->texCoords;
    struct normal *pnorm = object->normais;
    struct face *pface = object->faces;
    char buf[128], *pbuf;
    int i;

    while (!feof(file)) {
        /* Read whole line */
        fgets(buf, sizeof (buf), file);

        switch (buf[0]) {
            case 'v':
            {
                if (buf[1] == ' ') {
                    /* Vertex */
                    if (sscanf(buf + 2, "%f %f %f %f",
                            &pvert->xyzw[0], &pvert->xyzw[1],
                            &pvert->xyzw[2], &pvert->xyzw[3]) != 4) {
                        if (sscanf(buf + 2, "%f %f %f", &pvert->xyzw[0],
                                &pvert->xyzw[1], &pvert->xyzw[2]) != 3) {
                            fprintf(stderr, "Error reading vertex data!\n");
                            return 0;
                        } else {
                            pvert->xyzw[3] = 1.0;
                        }
                    }

                    pvert++;
                } else if (buf[1] == 't') {
                    /* Texture coords. */
                    if (sscanf(buf + 2, "%f %f %f", &puvw->uvw[0],
                            &puvw->uvw[1], &puvw->uvw[2]) != 3) {
                        if (sscanf(buf + 2, "%f %f", &puvw->uvw[0],
                                &puvw->uvw[1]) != 2) {
                            if (sscanf(buf + 2, "%f", &puvw->uvw[0]) != 1) {
                                fprintf(stderr, "Error reading texture coordinates!\n");
                                return 0;
                            } else {
                                puvw->uvw[1] = 0.0;
                                puvw->uvw[2] = 0.0;
                            }
                        } else {
                            puvw->uvw[2] = 0.0;
                        }
                    }

                    puvw++;
                } else if (buf[1] == 'n') {
                    /* Normal vector */
                    if (sscanf(buf + 2, "%f %f %f", &pnorm->ijk[0],
                            &pnorm->ijk[1], &pnorm->ijk[2]) != 3) {
                        fprintf(stderr, "Error reading normal vectors!\n");
                        return 0;
                    }

                    pnorm++;
                }

                break;
            }

            case 'f':
            {
                pbuf = buf;
                pface->quantidadeVertices = 0;

                /* Count number of vertices for this face */
                while (*pbuf) {
                    if (*pbuf == ' ')
                        pface->quantidadeVertices++;

                    pbuf++;
                }

                /* Select primitive type */
                if (pface->quantidadeVertices < 3) {
                    fprintf(stderr, "Error: a face must have at least 3 vertices!\n");
                    return 0;
                } else if (pface->quantidadeVertices == 3) {
                    pface->tipo = GL_TRIANGLES;
                } else if (pface->quantidadeVertices == 4) {
                    pface->tipo = GL_QUADS;
                } else {
                    pface->tipo = GL_POLYGON;
                }

                /* Memory allocation for vertices */
                pface->vertices = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                if (object->possuiTextura)
                    pface->texturas = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                if (object->possuiNormais)
                    pface->normais = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                /* Read face data */
                pbuf = buf;
                i = 0;

                for (i = 0; i < pface->quantidadeVertices; ++i) {
                    pbuf = strchr(pbuf, ' ');
                    pbuf++; /* Skip space */

                    /* Try reading vertices */
                    if (sscanf(pbuf, "%d/%d/%d",
                            &pface->vertices[i],
                            &pface->texturas[i],
                            &pface->normais[i]) != 3) {
                        if (sscanf(pbuf, "%d//%d", &pface->vertices[i],
                                &pface->normais[i]) != 2) {
                            if (sscanf(pbuf, "%d/%d", &pface->vertices[i],
                                    &pface->texturas[i]) != 2) {
                                sscanf(pbuf, "%d", &pface->vertices[i]);
                            }
                        }
                    }

                    /* Indices must start at 0 */
                    pface->vertices[i]--;

                    if (object->possuiTextura)
                        pface->texturas[i]--;

                    if (object->possuiNormais)
                        pface->normais[i]--;
                }

                pface++;
                break;
            }
        }
    }

    printf("second pass results: read\n");
    printf("   * %li vertices\n", pvert - object->vertices);
    printf("   * %li texture coords.\n", puvw - object->texCoords);
    printf("   * %li normal vectors\n", pnorm - object->normais);
    printf("   * %li faces\n", pface - object->faces);

    return 1;
}

int parseObjectFile(const char *filename, Object *object) {
    FILE *file;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
        return 0;
    }

    /* reset model data */
    memset(object, 0, sizeof (struct object));

    /* first pass: read model info */
    if (!initializeObject(file, object)) {
        fclose(file);
        return 0;
    }

    rewind(file);

    /* memory allocation */
    if (!createObject(object)) {
        fclose(file);
        resetModel(object);
        return 0;
    }

    /* second pass: read model data */
    if (!populateObject(file, object)) {
        fclose(file);
        resetModel(object);
        return 0;
    }

    fclose(file);
    return 1;
}

void drawObject(Object *object) {
    int i, j;

    for (i = 0; i < object->quantidadeFaces; ++i) {
        glBegin(object->faces[i].tipo);
        for (j = 0; j < object->faces[i].quantidadeVertices; ++j) {
            if (object->possuiTextura)
                glTexCoord3fv(object->texCoords[object->faces[i].texturas[j]].uvw);

            if (object->possuiNormais)
                glNormal3fv(object->normais[object->faces[i].normais[j]].ijk);

            glVertex4fv(object->vertices [object->faces[i].vertices[j]].xyzw);
        }
        glEnd();
    }
}

void drawFloor() {
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3f(-20, -0.5, 20);
    glVertex3f(20, -0.5, 20);
    glVertex3f(20, -0.5, -20);
    glVertex3f(-20, -0.5, -20);
    glEnd();
    glPopMatrix();
}

void init(const char *filename) {
    GLfloat lightpos[] = {5.0f, 10.0f, 0.0f, 1.0f};
    /* Initialize OpenGL context */
    glClearColor(0.5f, 0.5f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* Load OBJ model file */
    if (!parseObjectFile(filename, &object))
        exit(EXIT_FAILURE);
}

void resetScene() {
    resetModel(&object);
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

    /* Draw the model */
    drawObject(&object);
    drawFloor();
    glFlush(); //aaaa
    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            cameraX -= 0.2;
            cameraZ += 0.2;
            break;
        case GLUT_KEY_RIGHT:
            cameraX += 0.2;
            cameraZ -= 0.2;
            break;
        case GLUT_KEY_UP:
            cameraY += 0.2;
            break;
        case GLUT_KEY_DOWN:
            cameraY -= 0.2;
            break;
        case GLUT_KEY_HOME:
            cameraZ += 0.2;
            break;
        case GLUT_KEY_END:
            cameraZ -= 0.2;
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

    atexit(resetScene);
    init("casa.obj");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);

    glutMainLoop();

    return 0;
}
