#ifndef DT_SPHPROCS_H
#define DT_SPHPROCS_H

#include "DT_Procs.h"
#include "DT_SphPrim.h"


class DT_SphProcs : public DT_Procs {
public:
    DT_SphProcs();
    ~DT_SphProcs();
    int primType();
    void primNormal(vec3, vec3 *);
    short int primIntersection(ray, double *);
    void boundingBox(bbox *);
    void setPrim(DT_SphPrim *);
    DT_SphPrim *getPrim();

private:
    DT_SphPrim *prim;
};

#endif
