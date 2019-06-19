#ifndef DT_POLYPRIM_H
#define DT_POLYPRIM_H

#include "DT_Prim.h"


class DT_PolyPrim : public DT_Prim {
public:
    DT_PolyPrim();
    ~DT_PolyPrim();
    short int getNumVertices();
    void setNumVertices(short int);
    vec3 *getPoints();
    void setPoints(vec3 *);
    vec3 *getUVCoordinates();
    void setUVCoordinates(vec3 *);
    vec3 *getVertexNormals();
    void setVertexNormals(vec3 *);

private:
    short int nverts;
    vec3 *points;
    vec3 *uvs;
    vec3 *vnorms;
};

#endif
