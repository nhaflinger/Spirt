#ifndef LIBUTIL_H
#define LIBUTIL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

//#define NDEBUG
#include <assert.h>

#define PI (3.1415926535897932384626433832795)
#define SPHERE 0
#define POLYGON 1
#define XRES 640
#define YRES 486
#define XSAMPLES 1
#define YSAMPLES 1
#define FILTERWIDTH 1
#define BOX 0
#define TRIANGLE 1
#define EPS 1.0e-07
#define INF 1.0e38
#define BACKGROUND 0
#define SMALLBUFFER 256
#define LARGEBUFFER 1024
#define BLACKPOINT1 0
#define WHITEPOINT1 255
#define BLACKPOINT2 0
#define WHITEPOINT2 65535
#define NBYTES 1
#define ONE1 255
#define ONE2 65535
#define DITHER 0.5
#define RAYDEPTH 1
#define VOXPOP 8
#define VOXDEPTH 24
#define FLAT 0
#define SMOOTH 1
#define SCANDEPTH 16
#define RAYTRACED 0
#define SHADOWMAP 1

typedef struct {
    int numProcs;
    int numLight;
    int numPoly;
    int numSph;
    int numMaterial;
    int rayDepth;
    int lastRayShadowHit;
} globals;

typedef struct {
    double x;
    double y;
    double z;
} vec3;

typedef struct {
    double x;
    double y;
    double z;
    double w;
} vec4;

typedef struct {
    int vert0;
    int vert1;
    int vert2;
} triPoly;

typedef struct {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
} bbox;

typedef struct {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
} sw;

typedef struct {
    double left;
    double right;
    double top;
    double bottom;
} cw;

typedef struct {
    double r;
    double g;
    double b;
    double a;
} rgba;

typedef struct {
    double ka;
    double kd;
    double ks;
    double kt;
    double ke;
    double ns;
    rgba color;
    double refrindex;
    double kg;
    double kr;
} material;

typedef struct {
    double intensity;
    rgba color;
    vec3 from;
    vec3 to;
    int nondiffuse;
    int nonspecular;
} light;

typedef struct {
    double radius;
    vec3 c;
} sphere;

typedef struct {
    vec3 o;
    vec3 d;
} ray;

typedef struct {
    int xres;
    int yres;
    double aspect;
    sw screenWindow;
    cw cropWindow;
    double nearClip;
    double farClip;
} dsp;

typedef struct {
    double au;
    double bu;
    double av;
    double bv;
    double s;
    vec3 u;
    vec3 v;
    vec3 w;
} prj;

typedef struct {
    double element[4][4];
} mat4x4;

typedef struct {
    int numU;
    int numV;
    int orderU;
    int orderV;
    double *knotsU;
    double *knotsV;
    vec4 *points;
} nurbSurface;

typedef struct {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
} extents2D;


/* dot product */
double dotp(vec3 a, vec3 b);

/* cross product */
vec3 cross(vec3 a, vec3 b);

/* magnitude */
double length(vec3 a);

/* clamp */
double clamp(double a, double min, double max);

/* normalize */
vec3 normalize(vec3 b);

/* set point */
vec3 point(double x, double y, double z);

/* scalar multiplication */
vec3 operator * (double a, vec3 b);
vec3 operator * (vec3 a, double b);

/* scalar division */
vec3 operator / (double a, vec3 b);
vec3 operator / (vec3 a, double b);

/* addition */
vec3 operator + (vec3 a, vec3 b);

/* subtraction */
vec3 operator - (vec3 a, vec3 b);

/* equality */
int operator == (vec3 a, vec3 b);

/* set color */
rgba color(double r, double g, double b, double a);

/* scalar multiplication */
rgba operator * (double a, rgba b);
rgba operator * (rgba a, double b);
rgba operator * (rgba a, rgba b);

/* scalar division */
rgba operator / (double a, rgba b);
rgba operator / (rgba a, double b);

/* addition */
rgba operator + (rgba a, rgba b);

/* subtraction */
rgba operator - (rgba a, rgba b);

/* equality */
rgba operator == (rgba a, rgba b);

/* gamma */
rgba cgamma(rgba a, double b);

/* clamp */
rgba clamp(rgba a, double min, double max);

/* reflect */
vec3 reflect(vec3 d, vec3 n);

/* refract */
vec3 refract(double eta, vec3 d, vec3 n);

/* orient vector towards camera */
vec3 faceForward(vec3 n, vec3 d);

/* identity matrix */
void identity(mat4x4 *a);

/* set matrix */
void mset(mat4x4 *a, mat4x4 *b);

/* matrix scalar multiplication */
void mscalar(mat4x4 *a, double b, mat4x4 *c);

/* matrix multiplication */
void mmult(mat4x4 *a, mat4x4 *b, mat4x4 *c);

/* determinant of a 2x2 matrix */
double det2x2(double a, double b, double c, double d);

/* determinant of a 3x3 matrix */
double det3x3(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3);

/* determinant of a 4x4 matrix */
double det4x4(mat4x4 *a);

/* adjoint of matrix */
void adjoint(mat4x4 *a, mat4x4 *b);

/* inverse of matrix */
void inverse(mat4x4 *a, mat4x4 *b);

/* transform coordinates */
vec3 transform(vec3 xi, mat4x4 *a);

/* translate coordinates */
vec3 translate(vec3 xi, vec3 trans);

/* rotate coordinates */
vec3 rotate(vec3 xi, double angle, int axis);

/* load Houdini poly file */
void getPolyCount(char *filename, int *np, int *nv);
int loadPoly(char *filename, vec3 *vertices[3], vec3 *uvcoords[3], vec3 *vnorms[3], int np, int nv);

/* jittering a regular grid */
void randomSamples(int xsamples, int ysamples, double *rx, double *ry, double *rw, long seed);

/* convert degrees to radians */
double radians(double angle);

/* transform point into screen space */
vec3 toRaster(vec3 p, mat4x4 *c, double fov, sw screenWindow);

/* push entry to top of stack */
void push(int entry, int n, int *stack);

/* these random number functions seem to be missing in OSX */
#if 0
double drand48(void){
    return rand()/(double)RAND_MAX;
}

void srand48(long seedval){
    srand(seedval);
}
#endif

/* regular expression matching */
int match(const char *string, char *pattern);

/* quantize color data */
rgba quantize(rgba surfcol, double dither, int one, int blackpoint, int whitepoint);

/* smoothstep */
double smoothstep(double in, double out, double val);

#endif
