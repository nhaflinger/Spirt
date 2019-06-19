#include "DT_Prim.h"

DT_Prim::DT_Prim() { 
    visibility = 1; 
    info = "";
    shader = "default";
    castShadow = 0;
    shadowType = RAYTRACED;
    shadingInterp = FLAT;
    nsamples = 1;
}

DT_Prim::~DT_Prim() { 
    delete [] info;
}

short int DT_Prim::isVisible() {
    return visibility;
}

void DT_Prim::setVisibility(short int vis) {
    visibility = vis;
}

char *DT_Prim::getInfo() {
    return "null";
}

void DT_Prim::setInfo(char *i) {
    info = i;;
}

void DT_Prim::setMaterial(material *m) {
    surface = m;
}

material *DT_Prim::getMaterial() {
    return surface;
}

char *DT_Prim::getShader() {
    return shader;
}

void DT_Prim::setShader(char *s) {
    shader = s;
}

void DT_Prim::setCastShadow(short int c) {
    castShadow = c;
}

short int DT_Prim::getCastShadow() {
    return castShadow;
}

void DT_Prim::setShadowType(short int t) {
    shadowType = t;
}

short int DT_Prim::getShadowType() {
    return shadowType;
}

void DT_Prim::setShadingInterp(short int s) {
    shadingInterp = s;
}

short int DT_Prim::getShadingInterp() {
    return shadingInterp;
}

void DT_Prim::setNumSamples(int n) {
    nsamples = n;
}

int DT_Prim::getNumSamples() {
    return nsamples;
}

