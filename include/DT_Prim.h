#ifndef DT_PRIM_H
#define DT_PRIM_H

#include "libUtil.h"

class DT_Prim {
public:
    DT_Prim();
    ~DT_Prim();
    virtual short int isVisible();
    virtual void setVisibility(short int);
    virtual void setInfo(char *);
    virtual char *getInfo();
    virtual void setMaterial(material *);
    virtual material *getMaterial();
    virtual char *getShader();
    virtual void setShader(char *);
    virtual void setCastShadow(short int);
    virtual short int getCastShadow();
    virtual void setShadowType(short int);
    virtual short int getShadowType();
    virtual void setShadingInterp(short int);
    virtual short int getShadingInterp();
    virtual void setNumSamples(int);
    virtual int getNumSamples();

private:
    short int visibility;
    char *info;
    char *shader;
    material *surface;
    short int castShadow;
    short int shadowType;
    short int shadingInterp;
    int nsamples;
};

#endif
