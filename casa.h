#pragma once

typedef struct vertice Vertice;
typedef struct textura Textura;
typedef struct normal Normal;
typedef struct face Face;
typedef struct object Object;

Object object;
GLdouble cameraX, cameraY, cameraZ;

typedef float vec3_t[3];
typedef float vec4_t[4];

struct vertice {
    vec4_t xyzw;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

struct textura {
    vec3_t uvw;
    GLfloat u;
    GLfloat v;
    GLfloat w;
};

struct normal {
    vec3_t ijk;
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

    int possuiTextura;
    int possuiNormais;

    Vertice *vertices;
    Textura *texCoords;
    Normal *normais;
    Face *faces;
};