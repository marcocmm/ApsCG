#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

void resetModel(Object *object) {
    int i;

    if (object) {
        if (object->vertices) {
            free(object->vertices);
            object->vertices = NULL;
        }

        if (object->texturas) {
            free(object->texturas);
            object->texturas = NULL;
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

Object* createObject() {
    Object* object = (Object*) malloc(sizeof (Object));

    object->possuiNormais = 0;
    object->possuiTextura = 0;
    object->quantidadeFaces = 0;
    object->quantidadeNormais = 0;
    object->quantidadeTexturas = 0;
    object->quantidadeVertices = 0;

    object->faces = NULL;
    object->normais = NULL;
    object->texturas = NULL;
    object->vertices = NULL;

    memset(object, 0, sizeof (Object));
    return object;
}

int alocateMemmory(Object *object) {
    if (object->quantidadeVertices) {
        object->vertices = (Vertice *)
                malloc(sizeof (Vertice) * object->quantidadeVertices);
        if (!object->vertices)
            return 0;
    }

    if (object->quantidadeTexturas) {
        object->texturas = (Textura *)
                malloc(sizeof (Textura) * object->quantidadeTexturas);
        if (!object->texturas)
            return 0;
    }

    if (object->quantidadeNormais) {
        object->normais = (Normal *)
                malloc(sizeof (Normal) * object->quantidadeNormais);
        if (!object->normais)
            return 0;
    }

    if (object->quantidadeFaces) {
        object->faces = (Face *)
                calloc(object->quantidadeFaces, sizeof (Face));
        if (!object->faces)
            return 0;
    }

    return 1;
}

int countAttributes(FILE *file, Object *object) {
    int v, t, n;
    char buf[256];

    while (!feof(file)) {
        fgets(buf, sizeof (buf), file);

        switch (buf[0]) {
            case 'v':
            {
                if (buf[1] == ' ') {
                    object->quantidadeVertices++;
                } else if (buf[1] == 't') {
                    object->quantidadeTexturas++;
                } else if (buf[1] == 'n') {
                    object->quantidadeNormais++;
                } else {
                    printf("Warning: unknown token \"%s\"! (ignoring)\n", buf);
                }

                break;
            }

            case 'f':
            {
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
                    fprintf(stderr, "Error: found face with no vertex!\n");
                }

                break;
            }

            case 'g':
            {
                fscanf(file, "%s", buf);
                break;
            }

            default:
                break;
        }
    }

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
    Vertice *pvert = object->vertices;
    Textura *puvw = object->texturas;
    Normal *pnorm = object->normais;
    Face *pface = object->faces;
    char buf[128], *pbuf;
    int i;

    while (!feof(file)) {
        fgets(buf, sizeof (buf), file);

        switch (buf[0]) {
            case 'v':
            {
                if (buf[1] == ' ') {
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

                while (*pbuf) {
                    if (*pbuf == ' ')
                        pface->quantidadeVertices++;

                    pbuf++;
                }

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

                pface->vertices = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                if (object->possuiTextura)
                    pface->texturas = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                if (object->possuiNormais)
                    pface->normais = (int *) malloc(sizeof (int) * pface->quantidadeVertices);

                pbuf = buf;
                i = 0;

                for (i = 0; i < pface->quantidadeVertices; ++i) {
                    pbuf = strchr(pbuf, ' ');
                    pbuf++;

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
    printf("   * %li texture coords.\n", puvw - object->texturas);
    printf("   * %li normal vectors\n", pnorm - object->normais);
    printf("   * %li faces\n", pface - object->faces);

    return 1;
}

Object* parseObjectFile(const char *filename) {
    FILE *file;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
        return 0;
    }

    Object* object = createObject();

    if (!countAttributes(file, object)) {
        fclose(file);
        return 0;
    }

    rewind(file);

    if (!alocateMemmory(object)) {
        fclose(file);
        resetModel(object);
        return 0;
    }

    if (!populateObject(file, object)) {
        fclose(file);
        resetModel(object);
        return 0;
    }

    fclose(file);
    return object;
}

void drawObject(Object *object) {
    int i, j;
    for (i = 0; i < object->quantidadeFaces; ++i) {
        glBegin(object->faces[i].tipo);
        for (j = 0; j < object->faces[i].quantidadeVertices; ++j) {
            if (object->possuiTextura)
                glTexCoord3fv(object->texturas[object->faces[i].texturas[j]].uvw);

            if (object->possuiNormais)
                glNormal3fv(object->normais[object->faces[i].normais[j]].ijk);

            glVertex4fv(object->vertices [object->faces[i].vertices[j]].xyzw);
        }
        glEnd();
    }
}