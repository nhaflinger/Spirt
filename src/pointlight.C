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

    /* light direction */
    lt = lgts[i]->getLgtPrim()->getTransform();
    pp = point(0, 0, 0);
    pp = transform(pp, lt);
    //ld = normalize(pp - p);

    //lgtcol = lgts[i]->getLgtPrim()->getProperties()->intensity * lgts[i]->getLgtPrim()->getProperties()->color / dotp(ld, ld);
    lgtcol = lgts[i]->getLgtPrim()->getProperties()->intensity * lgts[i]->getLgtPrim()->getProperties()->color;

    return lgtcol;
}


