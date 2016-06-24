#pragma once

GLfloat rotate;
GLuint glGenList;
GLdouble obsX, obsY, obsZ;

/* Vectors */
typedef float vec3_t[3];
typedef float vec4_t[4];

/* Vertex */
struct vertice {
    vec4_t xyzw;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} Vertice;

/* Texture coordinates */
struct textura {
    GLfloat u;
    GLfloat v;
    GLfloat w;
    vec3_t uvw;
} Textura;

/* Normal vector */
struct normal {
    GLfloat i;
    GLfloat j;
    GLfloat k;
    vec3_t ijk;
} Normal;

/* Polygon */
struct face {
    GLenum tipo; /* primitive type */
    int size; /* number of vertices */

    int *vertices; /* vertex indices */
    int *texturas; /* texture coordinate indices */
    int *normais; /* normal vector indices */
} Face;

/* OBJ model structure */
struct object {
    int size; /* number of vertices */
    int num_texCoords; /* number of texture coords. */
    int num_normals; /* number of normal vectors */
    int num_faces; /* number of polygons */

    int has_texCoords; /* has texture coordinates? */
    int has_normals; /* has normal vectors? */

    struct vertice *vertices; /* vertex list */
    struct textura *texCoords; /* tex. coord. list */
    struct normal *normais; /* normal vector list */
    struct face *faces; /* model's polygons */
} Object;

struct object objfile;