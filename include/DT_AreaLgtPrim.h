#ifndef DT_AREALGTPRIM_H
#define DT_AREALGTPRIM_H

#include "DT_LgtPrim.h"
#include "DT_PolyPrim.h"


class DT_AreaLgtPrim : public DT_LgtPrim {
public:
    DT_AreaLgtPrim();
    ~DT_AreaLgtPrim();
    void setWidth(double);
    double getWidth();
    void setHeight(double);
    double getHeight();
    void setNumSamples(int);
    int getNumSamples();

private:
    double width;
    double height;
    int nsamples;
};

#endif
