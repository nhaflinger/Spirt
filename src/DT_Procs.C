#include "DT_Procs.h"

DT_Procs::DT_Procs() { }
DT_Procs::~DT_Procs() { }

int DT_Procs::primType() {
    return POLYGON;
}

void DT_Procs::primNormal(vec3 p, vec3 *n) {
}

short int DT_Procs::primIntersection(ray r, double *t) {
    return(0);
}

void DT_Procs::boundingBox(bbox *bb) {
}

void DT_Procs::setPrim(DT_Prim *prm) {
    prim = prm;
}

DT_Prim *DT_Procs::getPrim() {
   return prim;
}
