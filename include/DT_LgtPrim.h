#ifndef DT_LGTPRIM_H
#define DT_LGTPRIM_H

#include "DT_Prim.h"


class DT_LgtPrim : public DT_Prim {
public:
    DT_LgtPrim();
    ~DT_LgtPrim();
    virtual void setType(char *);
    virtual char *getType();
    virtual void setShader(char *);
    virtual char *getShader();
    virtual mat4x4 *getTransform();
    virtual void setTransform(mat4x4 *);
    virtual void setProperties(light *);
    virtual light *getProperties();

private:
    char *type;
    char *shader;
    mat4x4 *transform;
    light *properties;
};

#endif
