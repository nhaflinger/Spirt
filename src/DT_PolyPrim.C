#include "DT_PolyPrim.h"

DT_PolyPrim::DT_PolyPrim() { 
}

DT_PolyPrim::~DT_PolyPrim() { 
}

short int DT_PolyPrim::getNumVertices() {
    return nverts;
}

void DT_PolyPrim::setNumVertices(short int nv) {
    nverts = nv;
}

vec3 *DT_PolyPrim::getPoints() {
    return points;
}

void DT_PolyPrim::setPoints(vec3 *p) {
    points = p;
}

vec3 *DT_PolyPrim::getUVCoordinates() {
    return uvs;
}

void DT_PolyPrim::setUVCoordinates(vec3 *u) {
    uvs = u;
}

vec3 *DT_PolyPrim::getVertexNormals() {
    return vnorms;
}

void DT_PolyPrim::setVertexNormals(vec3 *v) {
    vnorms = v;
}

