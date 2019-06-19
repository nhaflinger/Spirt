#include "DT_SpotLgtPrim.h"

DT_SpotLgtPrim::DT_SpotLgtPrim() { 
}

DT_SpotLgtPrim::~DT_SpotLgtPrim() { 
}

void DT_SpotLgtPrim::setConeAngle(double c){
    coneangle = c;
}

double DT_SpotLgtPrim::getConeAngle(){
    return coneangle;
}

void DT_SpotLgtPrim::setConeDeltaAngle(double d){
    conedeltaangle = d;
}

double DT_SpotLgtPrim::getConeDeltaAngle(){
    return conedeltaangle;
}

void DT_SpotLgtPrim::setNumSamples(int n) {
    nsamples = n;
}

int DT_SpotLgtPrim::getNumSamples() {
    return nsamples;
}
