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
    vec3 pp, lv, to;
    mat4x4 *lt;
    double coneangle, conedeltaangle, theta, falloff;

    pp.x = 0;
    pp.y = 0;
    pp.z = 0;

    /* light direction */
    lt = lgts[i]->getLgtPrim()->getTransform();
    pp = transform(pp, lt);
    lv = normalize(pp - p);
    to = normalize(lgts[i]->getLgtPrim()->getProperties()->to);
    coneangle = ((DT_SpotLgtPrim *)lgts[i]->getLgtPrim())->getConeAngle();
    conedeltaangle = ((DT_SpotLgtPrim *)lgts[i]->getLgtPrim())->getConeDeltaAngle();

    theta = acos(dotp(lv, to));

    if(theta < radians(coneangle/2.)) {
        lgtcol = lgts[i]->getLgtPrim()->getProperties()->intensity * lgts[i]->getLgtPrim()->getProperties()->color;
    }
    else if(theta >= radians(coneangle/2.) && theta <= radians(coneangle/2. + conedeltaangle)) {
        lgtcol = lgts[i]->getLgtPrim()->getProperties()->intensity * lgts[i]->getLgtPrim()->getProperties()->color;
	falloff = 1 - smoothstep(radians(coneangle/2.), radians(coneangle/2. + conedeltaangle), theta);
	lgtcol = falloff * lgtcol;
    }
    else {
	lgtcol = color(0, 0, 0, 0);
    }

    return lgtcol;
}


