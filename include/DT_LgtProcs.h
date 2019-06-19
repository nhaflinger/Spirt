#ifndef DT_LGTPROCS_H
#define DT_LGTPROCS_H

#include "DT_LgtPrim.h"


class DT_LgtProcs {
public:
    DT_LgtProcs();
    ~DT_LgtProcs();
    void setLgtPrim(DT_LgtPrim *);
    virtual DT_LgtPrim *getLgtPrim();

private:
    DT_LgtPrim *lgtPrim;
};

#endif
