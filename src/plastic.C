#include "libShade.h"

#ifdef __cplusplus
extern "C" {
#endif

rgba surfaceColor(int m, ray r, vec3 p, vec3 n, int depth);

#ifdef __cplusplus
}
#endif


rgba surfaceColor(int m, ray r, vec3 p, vec3 n, int depth) {
    rgba surfcol, diffuse, specular;
    vec3 nf;
    double ambience, diffusivity, specularity, ns;

    surfcol = color(0, 0, 0, 1);

    nf = faceForward(normalize(n), normalize(r.d));

    ambience = procs[m]->getPrim()->getMaterial()->ka;
    if(ambience > 0) {
        surfcol = surfcol + ambience * ambient;
    }

    diffusivity = procs[m]->getPrim()->getMaterial()->kd;
    if(diffusivity > 0) {
        diffuse = diffusivity * procs[m]->getPrim()->getMaterial()->color * getDiffuse(nf, p, depth); 
        surfcol = surfcol + diffuse;
	surfcol.a = procs[m]->getPrim()->getMaterial()->color.a;
    }

    specularity = procs[m]->getPrim()->getMaterial()->ks;
    if(specularity > 0) {
        ns = procs[m]->getPrim()->getMaterial()->ns;
        specular = specularity * getSpecular(nf, p, ns, depth); 
        surfcol = surfcol + specular;
    }

    surfcol = clamp(surfcol, 0, 1);

    return surfcol;
}


