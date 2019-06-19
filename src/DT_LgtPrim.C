#include "DT_LgtPrim.h"

DT_LgtPrim::DT_LgtPrim() { 
    type = "point";
    shader = "pointlight";
}

DT_LgtPrim::~DT_LgtPrim() { 
}

void DT_LgtPrim::setType(char *t) {
    type = t;
}

char *DT_LgtPrim::getType() {
    return type;
}

void DT_LgtPrim::setShader(char *s) {
    shader = s;
}

char *DT_LgtPrim::getShader() {
    return shader;
}

mat4x4 *DT_LgtPrim::getTransform() {
    return transform;
}

void DT_LgtPrim::setTransform(mat4x4 *t) {
    transform = t;
}

void DT_LgtPrim::setProperties(light *l) {
    properties = l;
}

light *DT_LgtPrim::getProperties() {
    return properties;
}


