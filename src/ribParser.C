/*
   a simple rib parser

   by Doug Creel 2001-02
*/

#include "libUtil.h"
#include "DT_CamPrim.h"
#include "DT_OctTree.h"
#include "DT_AreaLgtProcs.h"
#include "DT_SphProcs.h"
#include "DT_PolyProcs.h"
#include "spirt.h"

static int currentFrame;
static int frameBlock;
static int worldBlock;
static int attributeBlock;
static int transformBlock;


int loadScene(char *filename);
void setFrame(char *str, int frame);
void setFormat(char *str, int *xres, int *yres, float *aspect); 
void setQuantize(char *str, int *white, int *black, int *one, float *dither);
void setDisplay(char *str, char *filename, char *driver, char *type);
void setPixelSamples(char *str, int *xs, int *ys); 
void setClipping(char *str, int *near, int *far); 
void setScreenWindow(char *str, float *xmin, float *xmax, float *ymin, float *ymax); 
void setCropWindow(char *str, float *left, float *right, float *bottom, float *top); 
void setConcatTransform(char *str, mat4x4 *m);
void setTransform(char *str, mat4x4 *m);
void setScale(char *str, float *xscale, float *yscale, float *zscale);
void setTranslate(char *str, float *xtranslate, float *ytranslate, float *ztranslate);
void setRotate(char *str, int *angle, float *xdirection, float *ydirection, float *zdirection);
void setSkew(char *str, float *xskew, float *yskew, float *zskew);
void setSphere(char *str, float *radius, float *zmin, float *zmax, float *thetamax);
//void setPolygon(char *str, ...);

void setFrame(char *str, int *frame) {
    int n;
    n = sscanf(str, "FrameBegin %d", frame);
}

void setFormat(char *str, int *xres, int *yres, float *aspect) {
    int n;
    n = sscanf(str, "Format %d %d %f", xres, yres, aspect);
}

void setQuantize(char *str, int *white, int *black, int *one, float *dither) {
    int n;
    n = sscanf(str, "Quantize \"rgba\" %d %d %d %f", white, black, one, dither);
}

void setDisplay(char *str, char *filename, char *driver, char *type) {
    int n;
    n = sscanf(str, "Display %s %s %s", filename, driver, type);
}

void setPixelSamples(char *str, int *xs, int *ys) {
    int n;
    n = sscanf(str, "PixelSamples %d %d", xs, ys);
}

void setClipping(char *str, float *near, float *far) {
    int n;
    n = sscanf(str, "Clipping %f %f", near, far);
}

void setScreenWindow(char *str, float *xmin, float *xmax, float *ymin, float *ymax) {
    int n;
    n = sscanf(str, "ScreenWindow %f %f %f %f", xmin, xmax, ymin, ymax);
}

void setCropWindow(char *str, float *left, float *right, float *bottom, float *top) {
    int n;
    n = sscanf(str, "CropWindow %f %f %f %f", left, right, bottom, top);
}

void setTransform(char *str, mat4x4 *m1) {
    int n;
    float m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33;

    n = sscanf(str, "Transform [%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f]", 
	       &m00, &m01, &m02, &m03, &m10, &m11, &m12, &m13, &m20, &m21, &m22, &m23,
	       &m30, &m31, &m32, &m33);
    m1->element[0][0] = m00;
    m1->element[0][1] = m01;
    m1->element[0][2] = m02;
    m1->element[0][3] = m03;
    m1->element[1][0] = m10;
    m1->element[1][1] = m11;
    m1->element[1][2] = m12;
    m1->element[1][3] = m13;
    m1->element[2][0] = m20;
    m1->element[2][1] = m21;
    m1->element[2][2] = m22;
    m1->element[2][3] = m23;
    m1->element[3][0] = m30;
    m1->element[3][1] = m31;
    m1->element[3][2] = m32;
    m1->element[3][3] = m33;
}

void setConcatTransform(char *str, mat4x4 *m1) {
    int n;
    float m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,m23,m30,m31,m32,m33;

    n = sscanf(str, "ConcatTransform [%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f]", 
	       &m00, &m01, &m02, &m03, &m10, &m11, &m12, &m13, &m20, &m21, &m22, &m23,
	       &m30, &m31, &m32, &m33);
    m1->element[0][0] = m00;
    m1->element[0][1] = m01;
    m1->element[0][2] = m02;
    m1->element[0][3] = m03;
    m1->element[1][0] = m10;
    m1->element[1][1] = m11;
    m1->element[1][2] = m12;
    m1->element[1][3] = m13;
    m1->element[2][0] = m20;
    m1->element[2][1] = m21;
    m1->element[2][2] = m22;
    m1->element[2][3] = m23;
    m1->element[3][0] = m30;
    m1->element[3][1] = m31;
    m1->element[3][2] = m32;
    m1->element[3][3] = m33;
}

void setScale(char *str, float *xscale, float *yscale, float *zscale) {
    int n;
    n = sscanf(str, "Scale %f %f %f", xscale, yscale, zscale);
}

void setTranslate(char *str, float *xtranslate, float *ytranslate, float *ztranslate) {
    int n;
    n = sscanf(str, "Translate %f %f %f", xtranslate, ytranslate, ztranslate);
}

void setRotate(char *str, int *angle, float *xdirection, float *ydirection, float *zdirection) {
    int n;
    n = sscanf(str, "Rotate %f %f %f %f", angle, xdirection, ydirection, zdirection);
}

void setSkew(char *str, float *xskew, float *yskew, float *zskew) {
    int n;
    n = sscanf(str, "Skew %f %f %f", xskew, yskew, zskew);
}


void setSphere(char *str, float *radius, float *zmin, float *zmax, float *thetamax) {
    int n;
    n = sscanf(str, "Sphere %f %f %f %f", radius, zmin, zmax, thetamax);
}

//void setPolygon(char *str, ...) {
//}


/* load scene file */
int loadScene(char *filename) {
    int i;
    FILE *fd;
    char *sptr, *dup;
    int nsph, npoly;
    int ns, np;
    char str[SMALLBUFFER];
    mat4x4 *coordSys = new mat4x4;
    DT_SphPrim *spheres;
    DT_PolyPrim *polygons;

    /* examine scene to determine the number of individual types of primitives */
    if(!(fd = fopen(filename, "r"))) {
        fprintf(stderr, "%s: File Not Found!\n", filename);
        return(0);
    }

    nsph = npoly = 0;
    while(1) {
        sptr = fgets(str, sizeof(str), fd);
        if(sptr == NULL) break;
        dup = strdup(sptr);

	if(match(dup, "^Sphere")) {
	    nsph += 1;
	}

	if(match(dup, "^Polygon"))  {
	    npoly += 1;
	}
    }

    rewind(fd);

    /* now build scene */

    /* define camera (we'll use default parameters) */
    cameras = new DT_CamPrim[NCAMERAS];
    dsp *display = cameras[0].getDisplay();

    /* define primitive spheres */
    if(nsph > 0) {
        spheres = new DT_SphPrim[nsph];
        procs1 = new DT_SphProcs[nsph];
        for(i=0; i<nsph; i++) {
            procs1[i].setPrim(&spheres[i]);
        }
    }

    /* define simple polygons */
    if(npoly > 0) {
        polygons = new DT_PolyPrim[npoly];
        procs2 = new DT_PolyProcs[npoly];
        for(i=0; i<npoly; i++) {
            procs2[i].setPrim(&polygons[i]);
        }
    }

    /* initialize parameters */
    identityMatrix(coordSys);
    ns = np = 0;

    /* read in data */
    while(1) {
        sptr = fgets(str, sizeof(str), fd);
        if(sptr == NULL) break;
        dup = strdup(sptr);

	if(match(dup, "^#")) {
	    continue;
	}

	if(match(dup, "^FrameBegin")) {
	    int *frame = new int;
	    frameBlock = 1;
	    setFrame(dup, frame);
	    currentFrame = *frame;
	    delete frame;
	}

	if(match(dup, "^FrameEnd")) {
	    frameBlock = 0;
	}

	if(match(dup, "^Identity")) {
            identityMatrix(coordSys);
	}

	if(match(dup, "^Format")) {
	    int *xres = new int;
	    int *yres = new int;
	    float *aspect = new float;
	    setFormat(dup, xres, yres, aspect);
	    display->xres = *xres;
	    display->yres = *yres;
	    display->aspect = *aspect;
	    delete xres;
	    delete yres;
	    delete aspect;
	}

	if(match(dup, "^Quantize")) {
	    int *white = new int;
	    int *black = new int;
	    int *one = new int;
	    float *dither = new float;
	    setQuantize(dup, white, black, one, dither);
	    delete white;
	    delete black;
	    delete one;
	    delete dither;
	}

	if(match(dup, "^Display")) {
	    char *filename = new char[LARGEBUFFER];
	    char *driver = new char[SMALLBUFFER];
	    char *type = new char[SMALLBUFFER];
	    setDisplay(dup, filename, driver, type);
	    //printf("DEBUG: %s %s %s\n", filename, driver, type);
	    delete [] filename;
	    delete [] driver;
	    delete [] type;
	}

	if(match(dup, "^PixelSamples")) {
	    int *xs = new int;
	    int *ys = new int;
	    setPixelSamples(dup, xs, ys);
	    xsamples = *xs;
	    ysamples = *ys;
	    delete xs;
	    delete ys;
	}

	if(match(dup, "^Clipping")) {
	    float *near = new float;
	    float *far = new float;
	    setClipping(dup, near, far);
	    display->nearClip = *near;
	    display->farClip = *far;
	    delete near;
	    delete far;
	}

	if(match(dup, "^ScreenWindow")) {
	    float *xmin = new float;
	    float *xmax = new float;
	    float *ymin = new float;
	    float *ymax = new float;
	    setScreenWindow(dup, xmin, xmax, ymin, ymax);
	    display->screenWindow.xmin = *xmin;
	    display->screenWindow.xmax = *xmax;
	    display->screenWindow.ymin = *ymin;
	    display->screenWindow.ymax = *ymax;
	    delete xmin;
	    delete xmax;
	    delete ymin;
	    delete ymax;
	}

	if(match(dup, "^CropWindow")) {
	    float *left = new float;
	    float *right = new float;
	    float *bottom = new float;
	    float *top = new float;
	    setCropWindow(dup, left, right, bottom, top);
	    display->cropWindow.left = *left;
	    display->cropWindow.right = *right;
	    display->cropWindow.bottom = *bottom;
	    display->cropWindow.top = *top;
	    delete left;
	    delete right;
	    delete bottom;
	    delete top;
	}

	if(match(dup, "^WorldBegin")) {
	    worldBlock = 1;
	}

	if(match(dup, "^WorldEnd")) {
	    worldBlock = 0;
	}

	if(match(dup, "^AttributeBegin")) {
	    attributeBlock += 1;
	}

	if(match(dup, "^AttributeEnd")) {
	    attributeBlock -= 1;
	}

	if(match(dup, "^TransformBegin")) {
	    transformBlock += 1;
	}

	if(match(dup, "^TransformEnd")) {
	    transformBlock -= 1;
	}

	if(match(dup, "^ConcatTransform")) {
            mat4x4 *m1 = new mat4x4;
	    setConcatTransform(dup, m1);
	    mset(coordSys, m1);
	    delete m1;
	}

	if(match(dup, "^Transform")) {
            mat4x4 *m1 = new mat4x4;
	    setTransform(dup, m1);
	    mset(coordSys, m1);
	    delete m1;
	}

	if(match(dup, "^Scale")) {
            mat4x4 *m1 = new mat4x4;
	    identityMatrix(m1);
	    float *sx = new float;
	    float *sy = new float;
	    float *sz = new float;
	    setScale(dup, sx, sy, sz);
	    m1->element[0][0] = *sx;
	    m1->element[1][1] = *sx;
	    m1->element[2][2] = *sx;
	    delete sx;
	    delete sy;
	    delete sz;
	    delete m1;
	}

	if(match(dup, "^Translate")) {
            mat4x4 *m1 = new mat4x4;
	    identityMatrix(m1);
	    float *dx = new float;
	    float *dy = new float;
	    float *dz = new float;
	    setTranslate(dup, dx, dy, dz);
	    m1->element[3][0] = *dx;
	    m1->element[3][1] = *dx;
	    m1->element[3][2] = *dx;
	    delete dx;
	    delete dy;
	    delete dz;
	    delete m1;
	}

	if(match(dup, "^Rotate")) {
            mat4x4 *m1 = new mat4x4;
	    identityMatrix(m1);
	    int *angle = new int;
	    float *dx = new float;
	    float *dy = new float;
	    float *dz = new float;
	    setRotate(dup, angle, dx, dy, dz);
	    delete angle;
	    delete dx;
	    delete dy;
	    delete dz;
	    delete m1;
	}

	if(match(dup, "^Skew")) {
            mat4x4 *m1 = new mat4x4;
	    identityMatrix(m1);
	    float *sx = new float;
	    float *sy = new float;
	    float *sz = new float;
	    setSkew(dup, sx, sy, sz);
	    delete sx;
	    delete sy;
	    delete sz;
	    delete m1;
	}

	if(match(dup, "^Sphere")) {
	    float *radius = new float;
	    float *zmin = new float;
	    float *zmax = new float;
	    float *thetamax = new float;
	    vec3 center = point(0, 0, 0);
            setSphere(dup, radius, zmin, zmax, thetamax);
	    spheres[ns].setRadius(*radius);
	    spheres[ns].setCenter(center);
	    delete radius;
	    delete zmin;
	    delete zmax;
	    delete thetamax;
	    ns += 1;
	}
    }

    fclose(fd);
}

void main(int argc, char *argv[]) {
    char *scenefile;
    int i;

    /* read command line arguments */
    if(argc > 2) {
	for(i=1; i<argc; i++) {
	    if(!strcmp(argv[i],"-s")) scenefile = argv[i+1];
	}
    }

    /* create scene database */
    frameBlock = 0;
    worldBlock = 0;
    attributeBlock = 0;
    transformBlock = 0;
    loadScene(scenefile);

    exit(1);
}





