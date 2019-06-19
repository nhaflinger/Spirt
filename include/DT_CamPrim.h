#ifndef DT_CAMPRIM_H
#define DT_CAMPRIM_H

#include "DT_Prim.h"


class DT_CamPrim : public DT_Prim {
public:
    DT_CamPrim();
    ~DT_CamPrim();
    double getFocal();
    void setType(char *);
    char *getType();
    void setFocal(double);
    double getAperture();
    void setAperture(double);
    vec3 getViewPoint();
    void setViewPoint(vec3);
    vec3 getViewDirection();
    void setViewDirection(vec3);
    vec3 getUpDirection();
    void setUpDirection(vec3);
    void setTransform(mat4x4 *);
    mat4x4 *getTransform();
    dsp *getDisplay();
    void setDisplay(dsp *);
    void getProjection(dsp *d, prj *proj);

private:
    char *type;
    double focal;
    double aperture;
    vec3 viewPoint;
    vec3 viewDirection;
    vec3 upDirection;
    mat4x4 *transform;
    dsp *display;
};

#endif
