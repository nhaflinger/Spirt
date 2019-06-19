#ifndef DT_SPOTLGTPRIM_H
#define DT_SPOTLGTPRIM_H

#include "DT_LgtPrim.h"
#include "DT_PolyPrim.h"


class DT_SpotLgtPrim : public DT_LgtPrim {
public:
    DT_SpotLgtPrim();
    ~DT_SpotLgtPrim();
    void setConeAngle(double);
    double getConeAngle();
    void setConeDeltaAngle(double);
    double getConeDeltaAngle();
    void setNumSamples(int);
    int getNumSamples();

private:
    double coneangle;
    double conedeltaangle;
    int nsamples;
};

#endif
