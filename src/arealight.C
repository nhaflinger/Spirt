#include "libShade.h"

#ifdef __cplusplus
extern "C" {
#endif

rgba lightColor(int i, vec3 p);

#ifdef __cplusplus
}
#endif


rgba lightColor(int i, vec3 p) {
    rgba lgtcol;
    vec3 pp, ld;
    mat4x4 *lt;
    int samples;
    double width, height;
    FloatLong seed;

    samples = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getNumSamples();
    width = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getWidth();
    height = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getHeight();
    seed.f = p.x + p.y + p.z;
    srand48(seed.l);

    /* light direction */
    lt = lgts[i]->getLgtPrim()->getTransform();
    if(samples <= 1) {
        pp = point(0, 0, 0);
    }
    else {
	pp = point((0.5 - drand48()) * width, 0., (0.5 - drand48()) * height);
    }
    pp = transform(pp, lt);
    ld = normalize(pp - p);

    lgtcol = lgts[i]->getLgtPrim()->getProperties()->intensity * lgts[i]->getLgtPrim()->getProperties()->color / dotp(ld, ld);

    return lgtcol;
}


