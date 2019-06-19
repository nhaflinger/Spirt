#ifndef DT_SCENE_H
#define DT_SCENE_H

#define NCAMERAS 1

globals *state;
DT_Procs **procs;
DT_LgtProcs **lgts;
DT_SphProcs *procs1;
DT_PolyProcs *procs2;
material *surf;
DT_LgtProcs *lgts1;
//DT_AreaLgtProcs *lgts1;
//DT_SpotLgtProcs *lgts1;
DT_CamPrim *cameras;
DT_OctTree *tree;
char *filterType;
int xsamples;
int ysamples;
int scandepth;
rgba ambient;
int nbytes;

#endif
