#ifndef DT_OCTTREE_H
#define DT_OCTTREE_H

#include "libUtil.h"
#include "DT_CamPrim.h"
#include "DT_Procs.h"

class DT_OctTree {
public:
    DT_OctTree();
    ~DT_OctTree();
    void setMaxDivs(int);
    short int getMaxDivs();
    void setMinObjs(int);
    short int getMinObjs();
    void buildOctTree(globals *s, DT_CamPrim *c, DT_Procs **p) {
	initOctTree(root, s, c, p);
    }
    int traverse(vec3 *);

private:
    class node {
    public:
        //int *objects;

    private:
        node *children[8];
        //bbox *bb;
    
    friend class DT_OctTree;
    };

    node *root;

    void initOctTree(node *&, globals *, DT_CamPrim *, DT_Procs **);

    short int maxDivs;
    short int minObjs;
};

#endif
