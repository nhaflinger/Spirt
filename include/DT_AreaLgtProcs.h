#ifndef DT_AREALGTPROCS_H
#define DT_AREALGTPROCS_H

#include "DT_LgtProcs.h"
#include "DT_AreaLgtPrim.h"


class DT_AreaLgtProcs : public DT_LgtProcs {
public:
    DT_AreaLgtProcs();
    ~DT_AreaLgtProcs();
    void setLgtPrim(DT_AreaLgtPrim *);
    DT_LgtPrim *getLgtPrim();

private:
    DT_AreaLgtPrim *lgtPrim;
};

#endif
