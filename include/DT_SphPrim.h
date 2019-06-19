#ifndef DT_SPHPRIM_H
#define DT_SPHPRIM_H

#include "DT_Prim.h"


class DT_SphPrim : public DT_Prim {
public:
    DT_SphPrim();
    ~DT_SphPrim();
    double getRadius();
    void setRadius(double);
    vec3 getCenter();
    void setCenter(vec3);

private:
    double radius;
    vec3 center;
};

#endif
