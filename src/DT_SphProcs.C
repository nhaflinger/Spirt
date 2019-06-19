#include "DT_SphProcs.h"

DT_SphProcs::DT_SphProcs() {};
DT_SphProcs::~DT_SphProcs() {};

/* primitive name */
int DT_SphProcs::primType() {
    return SPHERE;
}

/* sphere normal */
void DT_SphProcs::primNormal(vec3 p, vec3 *n) {
    *n = (1.0/prim->getRadius()) * (p - prim->getCenter());
}

/* ray-sphere intersection */
short int DT_SphProcs::primIntersection(ray r, double *t) {
    double at, bt, ct, disc, r1;
    short int hit;

    at = dotp(r.d, r.d);
    bt = dotp(2. * r.d, r.o - prim->getCenter());
    ct = dotp(r.o - prim->getCenter(), r.o - prim->getCenter()) - prim->getRadius() * prim->getRadius();
    disc = bt * bt - 4.0 * at * ct;

    if(disc < 0) {
        *t = 0;
	return 0;
    }
    else if(disc == 0) {
        *t = -bt/(2. * at);
	hit = 1;
    }
    else {
        *t = (-bt - sqrt(disc))/(2. * at);
	hit = 1;

	if(fabs(*t) < EPS) {
	    hit = 0;

	    r1 = (-bt + sqrt(disc))/(2. * at);
	    if(r1 > 0) {
		*t = r1;
		hit = 2;
	    }
	}
    }
    if(*t < 0) return 0;

    return hit;
}

void DT_SphProcs::boundingBox(bbox *bb) {
    vec3 c; 
    double r;
    bbox b1;

    c = prim->getCenter();
    r = prim->getRadius();

    b1.xmin = c.x - r;
    b1.xmax = c.x + r;
    b1.ymin = c.y - r;
    b1.ymax = c.y + r;
    b1.zmin = c.z - r;
    b1.zmax = c.z + r;

    *bb = b1;
}

void DT_SphProcs::setPrim(DT_SphPrim *prm) {
    prim = prm;
}

DT_SphPrim *DT_SphProcs::getPrim() {
   return prim;
}
