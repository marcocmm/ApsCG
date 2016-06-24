#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obj.h"

/**
 * Free resources allocated for the model.
 */
void resetModel(struct object *mdl) {
    int i;

    if (mdl) {
        if (mdl->vertices) {
            free(mdl->vertices);
            mdl->vertices = NULL;
        }

        if (mdl->texCoords) {
            free(mdl->texCoords);
            mdl->texCoords = NULL;
        }

        if (mdl->normais) {
            free(mdl->normais);
            mdl->normais = NULL;
        }

        if (mdl->faces) {
            for (i = 0; i < mdl->num_faces; ++i) {
                if (mdl->faces[i].vertices)
                    free(mdl->faces[i].vertices);

                if (mdl->faces[i].texturas)
                    free(mdl->faces[i].texturas);

                if (mdl->faces[i].normais)
                    free(mdl->faces[i].normais);
            }

            free(mdl->faces);
            mdl->faces = NULL;
        }
    }
}

/**
 * Allocate resources for the model after first pass.
 */
int createObject(struct object *mdl) {
    if (mdl->size) {
        mdl->vertices = (struct vertice *)
                malloc(sizeof (struct vertice) * mdl->size);
        if (!mdl->vertices)
            return 0;
    }

    if (mdl->num_texCoords) {
        mdl->texCoords = (struct textura *)
                malloc(sizeof (struct textura) * mdl->num_texCoords);
        if (!mdl->texCoords)
            return 0;
    }

    if (mdl->num_normals) {
        mdl->normais = (struct normal *)
                malloc(sizeof (struct normal) * mdl->num_normals);
        if (!mdl->normais)
            return 0;
    }

    if (mdl->num_faces) {
        mdl->faces = (struct face *)
                calloc(mdl->num_faces, sizeof (struct face));
        if (!mdl->faces)
            return 0;
    }

    return 1;
}

/**
 * Load an OBJ model from file -- first pass.
 * Get the number of triangles/vertices/texture coords for
 * allocating buffers.
 */
int initializeObject(FILE *fp, struct object *mdl) {
    int v, t, n;
    char buf[256];

    while (!feof(fp)) {
        /* Read whole line */
        fgets(buf, sizeof (buf), fp);

        switch (buf[0]) {
            case 'v':
            {
                if (buf[1] == ' ') {
                    /* Vertex */
                    mdl->size++;
                } else if (buf[1] == 't') {
                    /* Texture coords. */
                    mdl->num_texCoords++;
                } else if (buf[1] == 'n') {
                    /* Normal vector */
                    mdl->num_normals++;
                } else {
                    printf("Warning: unknown token \"%s\"! (ignoring)\n", buf);
                }

                break;
            }

            case 'f':
            {
                /* Face */
                if (sscanf(buf + 2, "%d/%d/%d", &v, &n, &t) == 3) {
                    mdl->num_faces++;
                    mdl->has_texCoords = 1;
                    mdl->has_normals = 1;
                } else if (sscanf(buf + 2, "%d//%d", &v, &n) == 2) {
                    mdl->num_faces++;
                    mdl->has_texCoords = 0;
                    mdl->has_normals = 1;
                } else if (sscanf(buf + 2, "%d/%d", &v, &t) == 2) {
                    mdl->num_faces++;
                    mdl->has_texCoords = 1;
                    mdl->has_normals = 0;
                } else if (sscanf(buf + 2, "%d", &v) == 1) {
                    mdl->num_faces++;
                    mdl->has_texCoords = 0;
                    mdl->has_normals = 0;
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
    if ((mdl->has_texCoords && !mdl->num_texCoords) ||
            (mdl->has_normals && !mdl->num_normals)) {
        fprintf(stderr, "error: contradiction between collected info!\n");
        return 0;
    }

    if (!mdl->size) {
        fprintf(stderr, "error: no vertex found!\n");
        return 0;
    }

    printf("first pass results: found\n");
    printf("   * %i vertices\n", mdl->size);
    printf("   * %i texture coords.\n", mdl->num_texCoords);
    printf("   * %i normal vectors\n", mdl->num_normals);
    printf("   * %i faces\n", mdl->num_faces);
    printf("   * has texture coords.: %s\n", mdl->has_texCoords ? "yes" : "no");
    printf("   * has normals: %s\n", mdl->has_normals ? "yes" : "no");

    return 1;
}

/**
 * Load an OBJ model from file -- first pass.
 * This time, read model data and feed buffers.
 */
int populateObject(FILE *fp, struct object *mdl) {
    struct vertice *pvert = mdl->vertices;
    struct textura *puvw = mdl->texCoords;
    struct normal *pnorm = mdl->normais;
    struct face *pface = mdl->faces;
    char buf[128], *pbuf;
    int i;

    while (!feof(fp)) {
        /* Read whole line */
        fgets(buf, sizeof (buf), fp);

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
                pface->size = 0;

                /* Count number of vertices for this face */
                while (*pbuf) {
                    if (*pbuf == ' ')
                        pface->size++;

                    pbuf++;
                }

                /* Select primitive type */
                if (pface->size < 3) {
                    fprintf(stderr, "Error: a face must have at least 3 vertices!\n");
                    return 0;
                } else if (pface->size == 3) {
                    pface->tipo = GL_TRIANGLES;
                } else if (pface->size == 4) {
                    pface->tipo = GL_QUADS;
                } else {
                    pface->tipo = GL_POLYGON;
                }

                /* Memory allocation for vertices */
                pface->vertices = (int *) malloc(sizeof (int) * pface->size);

                if (mdl->has_texCoords)
                    pface->texturas = (int *) malloc(sizeof (int) * pface->size);

                if (mdl->has_normals)
                    pface->normais = (int *) malloc(sizeof (int) * pface->size);

                /* Read face data */
                pbuf = buf;
                i = 0;

                for (i = 0; i < pface->size; ++i) {
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

                    if (mdl->has_texCoords)
                        pface->texturas[i]--;

                    if (mdl->has_normals)
                        pface->normais[i]--;
                }

                pface++;
                break;
            }
        }
    }

    printf("second pass results: read\n");
    printf("   * %li vertices\n", pvert - mdl->vertices);
    printf("   * %li texture coords.\n", puvw - mdl->texCoords);
    printf("   * %li normal vectors\n", pnorm - mdl->normais);
    printf("   * %li faces\n", pface - mdl->faces);

    return 1;
}

/**
 * Load an OBJ model from file, in two passes.
 */
int parseObjectFile(const char *filename, struct object *mdl) {
    FILE *fp;

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
        return 0;
    }

    /* reset model data */
    memset(mdl, 0, sizeof (struct object));

    /* first pass: read model info */
    if (!initializeObject(fp, mdl)) {
        fclose(fp);
        return 0;
    }

    rewind(fp);

    /* memory allocation */
    if (!createObject(mdl)) {
        fclose(fp);
        resetModel(mdl);
        return 0;
    }

    /* second pass: read model data */
    if (!populateObject(fp, mdl)) {
        fclose(fp);
        resetModel(mdl);
        return 0;
    }

    fclose(fp);
    return 1;
}

/**
 * Draw the OBJ model.
 */
void drawObject(struct object *mdl) {
    int i, j;

    for (i = 0; i < mdl->num_faces; ++i) {
        glBegin(mdl->faces[i].tipo);
        for (j = 0; j < mdl->faces[i].size; ++j) {
            if (mdl->has_texCoords)
                glTexCoord3fv(mdl->texCoords[mdl->faces[i].texturas[j]].uvw);

            if (mdl->has_normals)
                glNormal3fv(mdl->normais[mdl->faces[i].normais[j]].ijk);

            glVertex4fv(mdl->vertices [mdl->faces[i].vertices[j]].xyzw);
        }
        glEnd();
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

void init(const char *filename) {
    GLfloat lightpos[] = {5.0f, 10.0f, 0.0f, 1.0f};

    /* Initialize OpenGL context */
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* Load OBJ model file */
    if (!parseObjectFile(filename, &objfile))
        exit(EXIT_FAILURE);
}

void cleanup() {
    resetModel(&objfile);
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

    gluLookAt(obsX, obsY, obsZ,
            0, 0, 0,
            0, 1, 0);

    /* Draw the model */
    drawObject(&objfile);
    drawFloor();

    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            obsX -= 0.2;
            obsZ += 0.2;
            break;
        case GLUT_KEY_RIGHT:
            obsX += 0.2;
            obsZ -= 0.2;
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
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("OBJ Model");

    obsX = 10;
    obsY = 10;
    obsZ = 10;

    atexit(cleanup);
    init("casa.obj");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);

    glutMainLoop();

    return 0;
}
