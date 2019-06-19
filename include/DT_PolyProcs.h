#ifndef DT_POLYPROCS_H
#define DT_POLYPROCS_H

#include "DT_Procs.h"
#include "DT_PolyPrim.h"


class DT_PolyProcs : public DT_Procs {
public:
    DT_PolyProcs();
    ~DT_PolyProcs();
    int primType();
    void primNormal(vec3, vec3 *);
    short int primIntersection(ray, double *);
    void boundingBox(bbox *);
    void setPrim(DT_PolyPrim *);
    DT_Prim *getPrim();

private:
    DT_PolyPrim *prim;
};

#endif
