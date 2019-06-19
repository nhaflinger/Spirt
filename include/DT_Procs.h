#ifndef DT_PROCS_H
#define DT_PROCS_H

#include "DT_Prim.h"


class DT_Procs {
public:
    DT_Procs();
    ~DT_Procs();
    virtual int primType();
    virtual void primNormal(vec3, vec3 *);
    virtual short int primIntersection(ray, double *);
    virtual void boundingBox(bbox *);
    void setPrim(DT_Prim *);
    virtual DT_Prim *getPrim();

private:
    DT_Prim *prim;
};

#endif
