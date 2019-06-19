#ifndef LIBSHADE_H
#define LIBSHADE_H

#include <dlfcn.h>
#include <sys/types.h>
#include <time.h>
#include "libUtil.h"
#include "DT_CamPrim.h"
#include "DT_OctTree.h"
#include "DT_AreaLgtProcs.h"
#include "DT_SpotLgtProcs.h"
#include "DT_SphProcs.h"
#include "DT_PolyProcs.h"

#define ILLUMINANCE(x) for(x=0; x<state->numLight; x++)

extern globals *state;
extern DT_Procs **procs;
extern DT_LgtProcs **lgts;
extern DT_CamPrim *cameras;
extern DT_OctTree *tree;
extern rgba ambient;

typedef union {
    float f;
    long int l;
} FloatLong;

typedef rgba (*shader)(int m, ray r, vec3 p, vec3 n, int depth);
typedef rgba (*lgtshader)(int i, vec3 p);

int findClosestPoint(ray r, vec3 *p, int *m, int *np, double *t);
int rayShadow(ray rs, vec3 pp, rgba *color, int depth);
rgba getGlossyReflection(double glossiness, double reflectivity, ray r, vec3 nf, int n, int depth);
rgba getDiffuse(vec3 n, vec3 p, int depth);
rgba getSpecular(vec3 n, vec3 p, double ns, int depth);
rgba trace(ray r, int depth);
rgba surfaceShader(int m, ray r, vec3 p, vec3 n, int depth);
rgba lightShader(int i, vec3 p);

void sortPolygons(extents2D *ex, vec3 **nup);
void computeScanline(double line, int samples, double *rx, double *ry, extents2D *ex, vec3 *nup[3], int **scanline, prj *p);
rgba scan(int prim, ray r, int raydepth);

#endif

