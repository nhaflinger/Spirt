#include <stdio.h>
#include "DT_PolyProcs.h"

DT_PolyProcs::DT_PolyProcs() {};
DT_PolyProcs::~DT_PolyProcs() {};

/* primitive name */
int DT_PolyProcs::primType() {
    return POLYGON;
}

/* polygon normal */
void DT_PolyProcs::primNormal(vec3 p, vec3 *n) {
    short int nv;
    vec3 *points, *vnorms;
    double alpha, beta, a1, b1, c1, d1;
    vec3 w, u, v;

    nv = prim->getNumVertices();
    points = prim->getPoints();
    
    /* interpolate vertex normals (phong shading) */
    if(prim->getShadingInterp() == SMOOTH) {
        vnorms = prim->getVertexNormals();

	// see pp. 23,131 in "Practical Algorithms for 3D Computer Graphics" by R. Stuart Ferguson
	w = p - points[0];
	u = points[2] - points[0];
	v = points[1] - points[0];

	a1 = dotp(w, u);
	b1 = dotp(w, v);
	c1 = dotp(u, v);
	d1 = (dotp(u, u) * dotp(v, v) - c1 * c1);
	alpha = (a1 * dotp(v, v) - b1 * c1)/d1;
	beta = (b1 * dotp(u, u) - a1 * c1)/d1;

	*n = normalize(vnorms[0] + alpha * (vnorms[2] - vnorms[0]) + beta * (vnorms[1] - vnorms[0]));
    }
    else {
        *n = normalize(cross(points[1] - points[0], p - points[1]));
    }
}

/* ray-polygon intersection (this algorithm works only for convex polygons) */
short int DT_PolyProcs::primIntersection(ray r, double *t) {
    short int i, nv; 
    short int hit;
    vec3 *points;
    vec3 p, n;
    double c1, c2;
    double u0, v0, u1, v1, u2, v2;
    double alpha, beta;

    nv = prim->getNumVertices();
    points = prim->getPoints();

    n = cross(points[0] - points[1], points[2] - points[1]);
    c1 = (-1.0)*dotp(points[0], n);
    c2 = dotp(n, r.d);

    if(c2 == 0) {
	return 0;
    }

    *t = -(c1 + dotp(n, r.o))/c2;

    if(*t <= EPS) {
	return 0;
    }

    p = r.o + (*t) * r.d;

    /* Project polygon into primary plane and translate origin */
    hit = 0;
    i = 2;
    do {
        if((fabs(n.x) > fabs(n.y)) && (fabs(n.x) > fabs(n.z))) {
            u0 = p.y - points[0].y;
            v0 = p.z - points[0].z;
            u1 = points[i-1].y - points[0].y;
            v1 = points[i-1].z - points[0].z;
            u2 = points[i].y - points[0].y;
            v2 = points[i].z - points[0].z;
        }
        else if((fabs(n.y) > fabs(n.x)) && (fabs(n.y) > fabs(n.z))) {
            u0 = p.x - points[0].x;
            v0 = p.z - points[0].z;
            u1 = points[i-1].x - points[0].x;
            v1 = points[i-1].z - points[0].z;
            u2 = points[i].x - points[0].x;
            v2 = points[i].z - points[0].z;
        }
        else if((fabs(n.z) > fabs(n.x)) && (fabs(n.z) > fabs(n.y))) {
            u0 = p.x - points[0].x;
            v0 = p.y - points[0].y;
            u1 = points[i-1].x - points[0].x;
            v1 = points[i-1].y - points[0].y;
            u2 = points[i].x - points[0].x;
            v2 = points[i].y - points[0].y;
        }

	if(u1 == 0) {
	    beta = u0 / u2;
	    if((beta >= 0.) && (beta <= 1.)) {
		alpha = (v0 - beta * v2) / v1;
		hit = ((alpha >= 0.) && ((alpha + beta) <= 1.));
	    }
	}
	else {
	    beta = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
	    if((beta >= 0.) && (beta <= 1.)) {
		alpha = (u0 - beta * u2) / u1;
		hit = ((alpha >= 0.) && ((alpha + beta) <= 1.));
	    }
	}
    } while(!hit && (++i < nv));

    return hit;
}

void DT_PolyProcs::boundingBox(bbox *bb) {
    vec3 *v0;
    short int i, nv;
    bbox b1;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    
    nv = prim->getNumVertices();
    v0 = new vec3[nv];

    xmin = v0[0].x;
    ymin = v0[0].y;
    zmin = v0[0].z;
    xmax = v0[0].x;
    ymax = v0[0].y;
    zmax = v0[0].z;
    for(i=1; i<nv; i++) {
	if(v0[i].x < xmin)
	    xmin = v0[i].x;
        else if(v0[i].x > xmax)
	    xmax = v0[i].x;

	if(v0[i].y < ymin)
	    ymin = v0[i].y;
        else if(v0[i].y > ymax)
	    ymax = v0[i].y;

	if(v0[i].z < zmin)
	    zmin = v0[i].z;
        else if(v0[i].z > zmax)
	    zmax = v0[i].z;
    }

    b1.xmin = xmin;
    b1.xmax = xmax;
    b1.ymin = ymin;
    b1.ymax = ymax;
    b1.zmin = zmin;
    b1.zmax = zmax;

    *bb = b1;
}

void DT_PolyProcs::setPrim(DT_PolyPrim *prm) {
    prim = prm;
}

DT_Prim *DT_PolyProcs::getPrim() {
   return prim;
}
