#pragma once

typedef struct vertice Vertice;
typedef struct textura Textura;
typedef struct normal Normal;
typedef struct face Face;
typedef struct object Object;

typedef _Bool boolean;

struct vertice {
    GLfloat xyzw[4];
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

struct textura {
    GLfloat uvw[3];
    GLfloat u;
    GLfloat v;
    GLfloat w;
};

struct normal {
    GLfloat ijk[3];
    GLfloat i;
    GLfloat j;
    GLfloat k;
};

struct face {
    GLenum tipo;
    int quantidadeVertices;

    int *vertices;
    int *texturas;
    int *normais;
};

struct object {
    int quantidadeVertices;
    int quantidadeTexturas;
    int quantidadeNormais;
    int quantidadeFaces;

    boolean possuiTextura;
    boolean possuiNormais;

    Vertice *vertices;
    Textura *texturas;
    Normal *normais;
    Face *faces;
};

Object* parseObjectFile(const char *filename);

void drawObject(Object *object);

void resetModel(Object *object);