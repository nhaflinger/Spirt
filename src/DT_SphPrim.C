#include "DT_SphPrim.h"

DT_SphPrim::DT_SphPrim() { 
    radius = 1; 
    center.x = center.y = center.z = 0;
}

DT_SphPrim::~DT_SphPrim() { 
}

double DT_SphPrim::getRadius() {
    return radius;
}

void DT_SphPrim::setRadius(double r) {
    radius = r;
}

vec3 DT_SphPrim::getCenter() {
    return center;
}

void DT_SphPrim::setCenter(vec3 c) {
    center = c;
}

