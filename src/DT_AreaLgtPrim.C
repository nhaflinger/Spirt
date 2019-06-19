#include "DT_AreaLgtPrim.h"

DT_AreaLgtPrim::DT_AreaLgtPrim() { 
}

DT_AreaLgtPrim::~DT_AreaLgtPrim() { 
}

void DT_AreaLgtPrim::setWidth(double w){
    width = w;
}

double DT_AreaLgtPrim::getWidth(){
    return width;
}

void DT_AreaLgtPrim::setHeight(double h){
    height = h;
}

double DT_AreaLgtPrim::getHeight(){
    return height;
}

void DT_AreaLgtPrim::setNumSamples(int n) {
    nsamples = n;
}

int DT_AreaLgtPrim::getNumSamples() {
    return nsamples;
}
