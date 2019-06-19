#include "libShade.h"

#ifdef __cplusplus
extern "C" {
#endif

rgba surfaceColor(int m, ray r, vec3 p, vec3 n, int depth);

#ifdef __cplusplus
}
#endif


rgba surfaceColor(int m, ray r, vec3 p, vec3 n, int depth) {
    rgba surfcol, diffuse, specular, reflcol, refrcol;
    vec3 nf;
    ray refl, refr;
    double emissivity, ambience, diffusivity, specularity, reflectivity, 
        glossiness, transmissivity, ns, eta;

    surfcol = color(0, 0, 0, 1);

    nf = faceForward(normalize(n), normalize(r.d));

    emissivity = procs[m]->getPrim()->getMaterial()->ke;
    if(emissivity > 0) {
        surfcol = emissivity * procs[m]->getPrim()->getMaterial()->color;
        return surfcol;
    }

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

    /* secondary rays */
    if(depth < state->rayDepth) {
	/* if object is reflective */
	reflectivity = procs[m]->getPrim()->getMaterial()->kr;
	if(reflectivity > 0) {
	    glossiness = procs[m]->getPrim()->getMaterial()->kg;
	    if(glossiness > 0) {
	        refl.o = p;
	        refl.d = reflect(normalize(r.d), n);
		reflcol = getGlossyReflection(glossiness, reflectivity, refl, n, procs[m]->getPrim()->getNumSamples(), depth);
                surfcol = surfcol + reflcol;
	    }
	    else {
	        refl.o = p;
	        refl.d = reflect(normalize(r.d), n);
	        reflcol = reflectivity * trace(refl, depth+1);
                surfcol = surfcol + reflcol;
	    }
	}

	/* if object is transparent */
	transmissivity = procs[m]->getPrim()->getMaterial()->kt;
	if(transmissivity > 0) {
	    glossiness = procs[m]->getPrim()->getMaterial()->kg;
	    if(glossiness > 0) {
	        refr.o = p;
	        eta = procs[m]->getPrim()->getMaterial()->refrindex;
    
                if(dotp(normalize(r.d), n) >= 0) {
                    n = -1. * n;
                    eta = 1. / eta;
                }
        
	        refr.d = refract(eta, normalize(r.d), n);
		refrcol = getGlossyReflection(glossiness, transmissivity, refr, n, procs[m]->getPrim()->getNumSamples(), depth);
                surfcol = surfcol + refrcol;
	        surfcol.a *= transmissivity;
	    }
	    else {
	        refr.o = p;
	        eta = procs[m]->getPrim()->getMaterial()->refrindex;
    
                if(dotp(normalize(r.d), n) >= 0) {
                    n = -1. * n;
                    eta = 1. / eta;
                }
        
	        refr.d = refract(eta, normalize(r.d), n);
	        refrcol = transmissivity * trace(refr, depth+1);
                surfcol = surfcol + refrcol;
	        surfcol.a *= transmissivity;
	    }
	}
    }

    surfcol = clamp(surfcol, 0, 1);

    return surfcol;
}


