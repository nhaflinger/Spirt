#ifndef DT_SPOTLGTPROCS_H
#define DT_SPOTLGTPROCS_H

#include "DT_LgtProcs.h"
#include "DT_SpotLgtPrim.h"


class DT_SpotLgtProcs : public DT_LgtProcs {
public:
    DT_SpotLgtProcs();
    ~DT_SpotLgtProcs();
    void setLgtPrim(DT_SpotLgtPrim *);
    DT_LgtPrim *getLgtPrim();

private:
    DT_SpotLgtPrim *lgtPrim;
};

#endif
