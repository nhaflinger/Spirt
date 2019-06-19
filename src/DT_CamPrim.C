#include "DT_CamPrim.h"

DT_CamPrim::DT_CamPrim() { 
    type = "perspective";
    focal = 45; 
    aperture = 41.4214; 
    viewPoint.x = viewPoint.y = viewPoint.z = 0;
    viewDirection.x = viewDirection.y = 0;
    viewDirection.z = -1;
    upDirection.x = upDirection.z = 0;
    upDirection.y = 1;
    display = new dsp;
    display->xres = 640;
    display->yres = 480;
    display->aspect = 1.333;
    display->screenWindow.xmin = -display->aspect;
    display->screenWindow.xmax = display->aspect;
    display->screenWindow.ymin = -1;
    display->screenWindow.ymax = 1;
    display->cropWindow.left = 0;
    display->cropWindow.right = 1;
    display->cropWindow.top = 0;
    display->cropWindow.bottom = 1;
    display->nearClip = 1.0e-06;
    display->farClip = 1.0e30;
}

DT_CamPrim::~DT_CamPrim() { 
}

void DT_CamPrim::setType(char *t) {
    if(!strcmp(t, "perspective") || !strcmp(t, "orthographic")) type = t;
}

char *DT_CamPrim::getType() {
    return type;
}

double DT_CamPrim::getFocal() {
    return focal;
}

void DT_CamPrim::setFocal(double f) {
    focal = f;
}

double DT_CamPrim::getAperture() {
    return aperture;
}

void DT_CamPrim::setAperture(double a) {
    aperture = a;
}

vec3 DT_CamPrim::getViewPoint() {
    return viewPoint;
}

void DT_CamPrim::setViewPoint(vec3 p) {
    viewPoint = p;
}

vec3 DT_CamPrim::getViewDirection() {
    return viewDirection;
}

void DT_CamPrim::setViewDirection(vec3 v) {
    viewDirection = v;
}

vec3 DT_CamPrim::getUpDirection() {
    return upDirection;
}

void DT_CamPrim::setUpDirection(vec3 u) {
    upDirection = u;
}

mat4x4 *DT_CamPrim::getTransform() {
    return transform;
}

void DT_CamPrim::setTransform(mat4x4 *t) {
    transform = t;
}

dsp *DT_CamPrim::getDisplay() {
    return display;
}

void DT_CamPrim::setDisplay(dsp *d) {
    display->xres = d->xres;
    display->yres = d->yres;
    display->aspect = d->aspect;
    display->screenWindow.xmin = d->screenWindow.xmin;
    display->screenWindow.xmax = d->screenWindow.xmax;
    display->screenWindow.ymin = d->screenWindow.ymin;
    display->screenWindow.ymax = d->screenWindow.ymax;
    display->nearClip = d->nearClip;
    display->farClip = d->farClip;
}

/* uvw space parameters (camera projection) */
void DT_CamPrim::getProjection(dsp *d, prj *proj) {
    vec3 u, v, w;
    double au, av, bu, bv, s;

    w = -1 * normalize(getViewDirection());
    u = cross(getUpDirection(), w);
    u = normalize(u);
    v = cross(w, u);
    s = getFocal();
    au = 0.5 * (display->screenWindow.xmin) * getAperture();
    av = 0.5 * (display->screenWindow.ymin) * getAperture();
    bu = 0.5 * (display->screenWindow.xmax) * getAperture();
    bv = 0.5 * (display->screenWindow.ymax) * getAperture();

    proj->au = au;
    proj->bu = bu;
    proj->av = av;
    proj->bv = bv;
    proj->s = s;
    proj->u = u;
    proj->v = v;
    proj->w = w;
}

