#include "DT_OctTree.h"

DT_OctTree::DT_OctTree() { 
   root = NULL;
   maxDivs = VOXDEPTH;
   minObjs = VOXPOP;
}

DT_OctTree::~DT_OctTree() { 
}

void DT_OctTree::setMaxDivs(int d) {
    maxDivs = d;
}

short int DT_OctTree::getMaxDivs() {
    return maxDivs;
}

void DT_OctTree::setMinObjs(int m) {
    minObjs = m;
}

short int DT_OctTree::getMinObjs() {
    return minObjs;
}

void DT_OctTree::initOctTree(node *&newNode, globals *state, DT_CamPrim *camera, DT_Procs **procs) {
    int i, j;
    vec3 co;
    bbox bbo;
    bbox bbs;

    /* first get bounding box for scene (make sure to include camera) */
    co = camera[0].getViewPoint();
    bbs.xmin = co.x;
    bbs.ymin = co.y;
    bbs.zmin = co.z;
    bbs.xmax = co.x;
    bbs.ymax = co.y;
    bbs.zmax = co.z;

    for(i=0; i<state->numProcs; i++) {
	procs[i]->boundingBox(&bbo);

        if(bbo.xmin < bbs.xmin)
            bbs.xmin = bbo.xmin;
        else if(bbo.xmax > bbs.xmax)
            bbs.xmax = bbo.xmax;
        
        if(bbo.ymin < bbs.ymin)
            bbs.ymin = bbo.ymin;
        else if(bbo.ymax > bbs.ymax)
            bbs.ymax = bbo.ymax;
        
        if(bbo.zmin < bbs.zmin)
            bbs.zmin = bbo.zmin;
        else if(bbo.zmax > bbs.zmax)
            bbs.zmax = bbo.zmax;
    }

    if(newNode == NULL) {
	//newNode = new node;
	//for(i=0; i<8; i++) newNode->children[i] = NULL;
	//newNode->bb = &bbs;
    }

    //printf("DEBUG: %f %f\n",newNode->bb->xmin,newNode->bb->xmax);
    //printf("       %f %f\n",newNode->bb->ymin,newNode->bb->ymax);
    //printf("       %f %f\n",newNode->bb->zmin,newNode->bb->zmax);

    /* test for subdivision: if more than "minObjs" objects inside voxel - subdivide. */
    /* if there are "minObjs" objects or less you can stop subdividing at this leaf and */
    /* assign the list of objects to it */
}

int DT_OctTree::traverse(vec3 *p) {
    return 0;
}






