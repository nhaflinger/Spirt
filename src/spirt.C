/* 
   Spirit is a rendering test-bed which I began developing in the fall of 2001. 
   In its current form it is a hybrid ray tracer which incorporates a scan-line
   algorithm as a front-end to a Monte Carlo ray tracer.

   Doug Creel 2001-02
*/

#include "libUtil.h"
#include "sgilib.h"
#include "libShade.h"
#include "DT_CamPrim.h"
#include "DT_OctTree.h"
#include "DT_LgtProcs.h"
//#include "DT_AreaLgtProcs.h"
//#include "DT_SpotLgtProcs.h"
#include "DT_SphProcs.h"
#include "DT_PolyProcs.h"
#include "spirt.h"

void showUsage();
void buildScene(char *scenefile);


void showUsage() {
    fprintf(stderr,"Usage: spirt -res [x y] ...\n");
    fprintf(stderr,"Options:\n");
    fprintf(stderr,"    -res [x y]\n");
    fprintf(stderr,"    -focal [focal length]\n");
    fprintf(stderr,"    -aperture [field of view]\n");
    fprintf(stderr,"    -filter [filter type]\n");
    fprintf(stderr,"    -samples [xsamples ysamples]\n");
    fprintf(stderr,"    -raydepth [ray depth]\n");
    fprintf(stderr,"    -crop [left right top bottom]\n");
    fprintf(stderr,"    -screen [xmin xmax ymin ymax]\n");
    fprintf(stderr,"    -verbose\n");
    fprintf(stderr,"    -out [output file]\n");
    fprintf(stderr,"    -bytes [# of bytes (valid values are 1 or 2)]\n");
    fprintf(stderr,"    -threads [# of threads (should not exceed # of processors)]\n");
    exit(0);
}

void buildScene(char *scenefile) {
    double rad1, rad2;
    vec3 c1, c2, c1t;
    rgba col;
    int i, j, nsph, npoly, npp;
    vec3 *points1, *points2, *points3, *points4;
    vec3 *vnorms1, *vnorms2, *vnorms3, *vnorms4;
    mat4x4 *c1m = new mat4x4;
    mat4x4 *pm1 = new mat4x4;

    /* sphere parameters */
    nsph = 0;
    //nsph = 2;
    //c1 = vector(0, 0, 0);
    //rad1 = 1.00;
    //c2 = vector(2.0, -2.00, -6);
    //rad2 = 1.00;

    //identity(c1m);
    //c1m->element[3][0] = -2.0;
    //c1m->element[3][1] = -2.0;
    //c1m->element[3][2] = -8.0;
    //c1t = transform(c1, c1m);

    /* polygon parameters */
    npoly = 4;

    points1 = new vec3[3];
    points1[0] = vector(-100.00, -3.00, 3);
    points1[1] = vector(100.00, -3.00, 3);
    points1[2] = vector(100.00, -3.00, -17);
    vnorms1 = new vec3[3];
    vnorms1[0] = vector(0.0, 1.00, 0.0);
    vnorms1[1] = vector(0.0, 1.00, 0.0);
    vnorms1[2] = vector(0.0, 1.00, 0.0);

    points2 = new vec3[3];
    points2[0] = vector(-100.00, -3.00, 3);
    points2[1] = vector(100.00, -3.00, -17);
    points2[2] = vector(-100.00, -3.00, -17);
    vnorms2 = new vec3[3];
    vnorms2[0] = vector(0.0, 1.00, 0.0);
    vnorms2[1] = vector(0.0, 1.00, 0.0);
    vnorms2[2] = vector(0.0, 1.00, 0.0);

    points3 = new vec3[3];
    points3[0] = vector(-1.00, 5.0, -6);
    points3[1] = vector(-1.00, 5.0, -8);
    points3[2] = vector(1.00, 5.0, -8);
    vnorms3 = new vec3[3];
    vnorms3[0] = vector(0.0, -1.00, 0.0);
    vnorms3[1] = vector(0.0, -1.00, 0.0);
    vnorms3[2] = vector(0.0, -1.00, 0.0);

    points4 = new vec3[3];
    points4[0] = vector(-1.00, 5.0, -6);
    points4[1] = vector(1.00, 5.0, -8);
    points4[2] = vector(1.00, 5.0, -6);
    vnorms4 = new vec3[3];
    vnorms4[0] = vector(0.0, -1.00, 0.0);
    vnorms4[1] = vector(0.0, -1.00, 0.0);
    vnorms4[2] = vector(0.0, -1.00, 0.0);

    /* light parameters (rotate 180 about y and translate) */
    mat4x4 *l1m = new mat4x4;
    identity(l1m);
    l1m->element[1][0] = 0;
    l1m->element[1][1] = -1;
    l1m->element[1][2] = 0;
    l1m->element[3][0] = 0;
    l1m->element[3][1] = 5.0;
    l1m->element[3][2] = -7;
    col = color(1.0, 1.0, 1.0, 1.0);

    /* define spheres */
    //DT_SphPrim *spheres = new DT_SphPrim[nsph];
    //spheres[0].setRadius(rad1);
    //spheres[0].setCenter(c1t);
    //spheres[1].setRadius(rad2);
    //spheres[1].setCenter(c2);

    //procs1 = new DT_SphProcs[nsph];
    //procs1[0].setPrim(&spheres[0]);
    //procs1[1].setPrim(&spheres[1]);

    /* read in poly file */
    char *polyFile = "/shots/spi/home/dev/thedoug/src/geo/ferrari.poly";
    int fnp, fnv;
    getPolyCount(polyFile, &fnp, &fnv);
    vec3 *vertices[fnp];
    vec3 *vnorms[fnp];
    vec3 *uvcoords[fnp];
    for(i=0; i<fnp; i++) {
        vertices[i] = new vec3[3];
        uvcoords[i] = new vec3[3];
        vnorms[i] = new vec3[3];
    }
    loadPoly(polyFile, vertices, uvcoords, vnorms, fnp, fnv);

    /* rotate around y */
    identity(pm1);
    pm1->element[0][0] = 0.707;
    pm1->element[0][2] = 0.707;
    pm1->element[2][0] = -0.707;
    pm1->element[2][2] = 0.707;
    for(i=0; i<fnp; i++) {
        vertices[i][0] = transform(vertices[i][0], pm1);
        vertices[i][1] = transform(vertices[i][1], pm1);
        vertices[i][2] = transform(vertices[i][2], pm1);
    }

    /* transform points */
    identity(pm1);
    pm1->element[0][0] = 0.010;
    pm1->element[1][1] = 0.010;
    pm1->element[2][2] = 0.010;
    pm1->element[3][0] = .0;
    pm1->element[3][1] = -2.0;
    pm1->element[3][2] = -6.0;
    for(i=0; i<fnp; i++) {
        vertices[i][0] = transform(vertices[i][0], pm1);
        vertices[i][1] = transform(vertices[i][1], pm1);
        vertices[i][2] = transform(vertices[i][2], pm1);
    }

    /* define polygons */
    DT_PolyPrim *polys = new DT_PolyPrim[npoly+fnp];
    polys[0].setNumVertices(3);
    polys[0].setPoints(points1);
    polys[0].setVertexNormals(vnorms1);
    polys[0].setShadingInterp(FLAT);
    polys[0].setNumSamples(1);
    polys[1].setNumVertices(3);
    polys[1].setPoints(points2);
    polys[1].setVertexNormals(vnorms2);
    polys[1].setShadingInterp(FLAT);
    polys[1].setNumSamples(1);
    polys[2].setNumVertices(3);
    polys[2].setPoints(points3);
    polys[2].setVertexNormals(vnorms3);
    polys[2].setShadingInterp(FLAT);
    polys[3].setNumVertices(3);
    polys[3].setPoints(points4);
    polys[3].setVertexNormals(vnorms4);
    polys[3].setShadingInterp(FLAT);

    procs2 = new DT_PolyProcs[npoly+fnp];
    procs2[0].setPrim(&polys[0]);
    procs2[1].setPrim(&polys[1]);
    procs2[2].setPrim(&polys[2]);
    procs2[3].setPrim(&polys[3]);
    procs2[4].setPrim(&polys[4]);
    procs2[5].setPrim(&polys[5]);

    for(i=npoly; i<npoly+fnp; i++) {
        polys[i].setNumVertices(3);
        polys[i].setPoints(vertices[i-npoly]);
        polys[i].setUVCoordinates(uvcoords[i-npoly]);
        polys[i].setVertexNormals(vnorms[i-npoly]);
        polys[i].setShadingInterp(SMOOTH);
        procs2[i].setPrim(&polys[i]);
    }

    /* create some materials */
    state->numMaterial = 5;
    surf = new material[state->numMaterial];

    /* surface reflectance */
    surf[0].color = color(0.7, 0.7, 0.7, 1.0);
    surf[0].ks = 0.5;
    surf[0].kd = 0.5;
    surf[0].ka = 1.0;
    surf[0].kt = 0.0;
    surf[0].refrindex = 1.0;
    surf[0].ns = .1;
    surf[0].ke = 0.0;
    surf[0].kg = 0.0;
    surf[0].kr = 0.0;
    surf[1].color = color(0.7, 0.7, 0.7, 1.0);
    surf[1].ks = 0.0;
    surf[1].kd = 0.5;
    surf[1].ka = 0.0;
    surf[1].kt = 0.0;
    surf[1].ns = .05;
    surf[1].refrindex = 1.00;
    surf[1].ke = 0.0;
    surf[1].kg = 0.0;
    surf[1].kr = 0.0;
    surf[2].color = color(1.0, 1.0, 1.0, 1.0);
    surf[2].ks = 0.0;
    surf[2].kd = 0.0;
    surf[2].ka = 0.0;
    surf[2].kt = 0.0;
    surf[2].ke = 1.0;
    surf[2].kg = 0.0;
    surf[2].kr = 0.0;
    surf[3].color = color(1.0, 0.0, 0.0, 1.0);
    surf[3].ks = 0.9;
    surf[3].kd = 0.7;
    surf[3].ka = 0.0;
    surf[3].kt = 0.5;
    surf[3].ns = .05;
    surf[3].refrindex = 1.02;
    surf[3].ke = 0.0;
    surf[3].kg = 0.0;
    surf[3].kr = 0.1;
    surf[4].color = color(1.0, 1.0, 1.0, 1.0);
    surf[4].ks = 0.9;
    surf[4].kd = 0.7;
    surf[4].ka = 0.0;
    surf[4].kt = 0.0;
    surf[4].ns = .05;
    surf[4].refrindex = 1.0;
    surf[4].ke = 0.0;
    surf[4].kg = 0.0;
    surf[4].kr = 0.0;

    /* assign materials */
    //spheres[0].setMaterial(&surf[0]);
    //spheres[1].setMaterial(&surf[3]);
    polys[0].setMaterial(&surf[1]);
    polys[1].setMaterial(&surf[1]);
    polys[2].setMaterial(&surf[2]);
    polys[3].setMaterial(&surf[2]);

    for(i=npoly; i<npoly+fnp; i++) {
        polys[i].setMaterial(&surf[0]);
	polys[i].setShader("plastic");
    }

    /* define lights */
    DT_LgtPrim *light1 = new DT_LgtPrim;
    //DT_AreaLgtPrim *light1 = new DT_AreaLgtPrim;
    //DT_SpotLgtPrim *light1 = new DT_SpotLgtPrim;
    light1->setCastShadow(0);
    //light1->setWidth(2);
    //light1->setHeight(2);
    //light1->setType("area");
    //light1->setShader("arealight");
    //light1->setConeAngle(75);
    //light1->setConeDeltaAngle(5);
    light1->setType("point");
    light1->setShader("pointlight");
    //light1->setType("area");
    //light1->setShader("arealight");
    //light1->setType("spot");
    //light1->setShader("spotlight");
    light1->setNumSamples(1);
    light1->setTransform(l1m);
    light *lprops;
    lprops = new light;
    lprops->intensity = 1.00;
    lprops->color = col;
    lprops->from = vector(0, 0, 0);
    lprops->to = vector(0, 1, 0);
    lprops->nondiffuse = 1;
    lprops->nonspecular = 1;
    light1->setProperties(lprops);

    state->numLight = 1;
    lgts1 = new DT_LgtProcs[state->numLight];
    //lgts1 = new DT_AreaLgtProcs[state->numLight];
    //lgts1 = new DT_SpotLgtProcs[state->numLight];
    lgts1[0].setLgtPrim(light1);

    /* ambient light */
    ambient = color(0.0, 0.0, 0.0, 0.0);

    /* global parameters */
    state->numProcs = nsph + npoly + fnp;
    state->numSph = nsph;
    state->numPoly = npoly + fnp;

    /* clean up */
    delete c1m;
    delete pm1;
}


void main(int argc, char *argv[]) {
    int i, j, k, l, m, mx;
    double t;
    vec3 p, n, nf, ld, pc, nc;
    ray r, rs;
    char *outfile, *scenefile;
    unsigned short **rbuf, **gbuf, **bbuf, **abuf;
    double *rx, *ry, *rw;
    int hit = 0;
    int shad = 0;
    dsp *display;
    prj *proj;
    vec3 u, v, w;
    double au, av, bu, bv, s;
    int xres, yres;
    double focal, aperture;
    int filter;
    double n1, n2;
    cw cwin;
    sw swin;
    int blackpoint, whitepoint, one;
    int verbose = 0;
    state = new globals;
    int raydepth = 1;
    int threads = 1;
    int progress = 0;

    /* initialize display settings */
    xres = XRES;
    yres = YRES;
    focal = 45;
    aperture = 41.4214/2.;
    cwin.left = 0;
    cwin.right = 1;
    cwin.top = 0;
    cwin.bottom = 1;
    swin.xmin = -(double)xres/(double)yres;
    swin.xmax = (double)xres/(double)yres;
    swin.ymin = -1;
    swin.ymax = 1;
    xsamples = XSAMPLES;
    ysamples = YSAMPLES;
    nbytes = NBYTES;
    state->rayDepth = RAYDEPTH;
    state->lastRayShadowHit = 0;
    filterType = "box";
    outfile = "test.rgb";
    scenefile = "scene.dat";

    /* read command line arguments */
    if(argc > 1) {
	for(i=1; i<argc; i++) {
	    if(!strcmp(argv[i],"-res")) {
		xres = atoi(argv[i+1]);
		yres = atoi(argv[i+2]);
	    }
	    if(!strcmp(argv[i],"-raydepth")) 
		state->rayDepth = atoi(argv[i+1]);
	    if(!strcmp(argv[i],"-focal")) 
		focal = atoi(argv[i+1]);
	    if(!strcmp(argv[i],"-aperture")) 
		aperture = atoi(argv[i+1]);
	    if(!strcmp(argv[i],"-samples")) {
		xsamples = atoi(argv[i+1]);
		ysamples = atoi(argv[i+2]);
	    }
	    if(!strcmp(argv[i],"-filter")) 
		filterType = argv[i+1];
	    if(!strcmp(argv[i],"-crop")) {
		cwin.left = atof(argv[i+1]);
		cwin.right = atof(argv[i+2]);
		cwin.top = atof(argv[i+3]);
		cwin.bottom = atof(argv[i+4]);
	    }
	    if(!strcmp(argv[i],"-screen")) {
		swin.xmin = atof(argv[i+1]);
		swin.xmax = atof(argv[i+2]);
		swin.ymin = atof(argv[i+3]);
		swin.ymax = atof(argv[i+4]);
	    }
	    if(!strcmp(argv[i],"-verbose")) 
		verbose = 1;
	    if(!strcmp(argv[i],"-out")) 
                outfile = argv[i+1];
	    if(!strcmp(argv[i],"-scene")) 
                scenefile = argv[i+1];
	    if(!strcmp(argv[i],"-bytes")) 
		nbytes = atoi(argv[i+1]);
	    if(!strcmp(argv[i],"-threads")) 
		threads = atoi(argv[i+1]);
	    if(!strcmp(argv[i],"-h"))
		showUsage();
	    if(!strcmp(argv[i],"-u"))
		showUsage();
	}
    }
    else {
	showUsage();
    }

    /* threads */
    //pthread_t threadID[threads];

    /* create scene database */
    if(verbose) fprintf(stderr,"Loading scene ...\n");
    buildScene(scenefile);

    /* create array of procs base class pointers */
    procs = new DT_Procs*[state->numProcs];
    for(i=0; i<state->numProcs; i++) procs[i] = new DT_Procs;
    for(i=0; i<state->numSph; i++) procs[i] = &procs1[i];
    for(i=state->numSph; i<state->numProcs; i++) procs[i] = &procs2[i-state->numSph];

    /* create array of lgts base class pointers */
    lgts = new DT_LgtProcs*[state->numLight];
    for(i=0; i<state->numLight; i++) lgts[i] = new DT_LgtProcs;
    for(i=0; i<state->numLight; i++) lgts[i] = &lgts1[i];


    /* update display settings */
    cameras = new DT_CamPrim[NCAMERAS];
    display = cameras[0].getDisplay();
    display->xres = xres;
    display->yres = yres;
    display->aspect = (double)xres/(double)yres;
    display->cropWindow.left = cwin.left;
    display->cropWindow.right = cwin.right;
    display->cropWindow.top = cwin.top;
    display->cropWindow.bottom = cwin.bottom;
    display->screenWindow.xmin = -display->aspect;
    display->screenWindow.xmax = display->aspect;
    display->screenWindow.ymin = -1.;
    display->screenWindow.ymax = 1.;
    cameras[0].setFocal(focal);
    cameras[0].setAperture(aperture);

    /* set quantization */
    if(nbytes == 2) {
	blackpoint = BLACKPOINT2;
	whitepoint = WHITEPOINT2;
	one = ONE2;
    }
    else {
	blackpoint = BLACKPOINT1;
	whitepoint = WHITEPOINT1;
	one = ONE1;
    }

    /* ray origin */
    vec3 viewpnt;
    viewpnt.x = 0;
    viewpnt.y = -1;
    viewpnt.z = 4;
    cameras[0].setViewPoint(viewpnt);
    r.o = cameras[0].getViewPoint();

    /* ray direction */
    r.d = cameras[0].getViewDirection();

    /* set camera viewing transform */
    vec3 vpn, vup, vrp, nn, un, vn;
    vpn = cameras[0].getViewDirection();
    vup = cameras[0].getUpDirection();
    vrp = cameras[0].getViewPoint();
    nn = normalize(-1. * vpn);
    un = normalize(cross(vup, -1. * vpn));
    vn = cross(nn, un);
    mat4x4 *cm = new mat4x4;
    identity(cm);
    nn = normalize(vpn);
    cm->element[0][0] = un.x;
    cm->element[0][1] = un.y;
    cm->element[0][2] = un.z;
    cm->element[1][0] = vn.x;
    cm->element[1][1] = vn.y;
    cm->element[1][2] = vn.z;
    cm->element[2][0] = nn.x;
    cm->element[2][1] = nn.y;
    cm->element[2][2] = nn.z;
    cm->element[3][0] = -(un.x * vrp.x + un.y * vrp.y + un.z * vrp.z);
    cm->element[3][1] = -(vn.x * vrp.x + vn.y * vrp.y + vn.z * vrp.z);
    cm->element[3][2] = -(nn.x * vrp.x + nn.y * vrp.y + nn.z * vrp.z);
    cameras[0].setTransform(cm);

    /* construct tree */
    //tree = new DT_OctTree;
    //tree->buildOctTree(state, cameras, procs);

    /* uvw space parameters (camera projection) */
    w = -1 * normalize(cameras[0].getViewDirection());
    u = cross(cameras[0].getUpDirection(), w);
    u = normalize(u);
    v = cross(w, u);
    s = cameras[0].getFocal();
    au = 0.5 * (display->screenWindow.xmin) * cameras[0].getAperture();
    av = 0.5 * (display->screenWindow.ymin) * cameras[0].getAperture();
    bu = 0.5 * (display->screenWindow.xmax) * cameras[0].getAperture();
    bv = 0.5 * (display->screenWindow.ymax) * cameras[0].getAperture();

    proj = new prj;
    proj->au = au;
    proj->bu = bu;
    proj->av = av;
    proj->bv = bv;
    proj->s = s;
    proj->u = u;
    proj->v = v;
    proj->w = w;

    /* set pixel buffer */
    rbuf = new unsigned short*[display->yres];
    gbuf = new unsigned short*[display->yres];
    bbuf = new unsigned short*[display->yres];
    abuf = new unsigned short*[display->yres];
    for(i=0; i<display->yres; i++) {
        rbuf[i] = new unsigned short[display->xres];
        gbuf[i] = new unsigned short[display->xres];
        bbuf[i] = new unsigned short[display->xres];
        abuf[i] = new unsigned short[display->xres];
    }

    /* random samples */
    if(xsamples < 1) xsamples = 1;
    if(ysamples < 1) ysamples = 1;
    rx = new double[xsamples*ysamples];
    ry = new double[xsamples*ysamples];
    rw = new double[xsamples*ysamples];
    long ix = 0;
    randomSamples(xsamples, ysamples, rx, ry, rw, ix);

    /* scan-line data */
    int **scanline = new int*[display->xres];
    for(k=0; k<display->xres; k++) scanline[k] = new int[xsamples*ysamples];

    int *i0 = new int[state->numPoly];
    int *i1 = new int[state->numPoly];
    vec3 **nup = new vec3*[state->numPoly];
    for(k=0; k<state->numPoly; k++) nup[k] = new vec3[3];

    /* sort polygons */
    if(verbose) fprintf(stderr,"Sorting ...\n");
    sortPolygons(i0, i1, nup);
    if(verbose) fprintf(stderr,"%d polygons sorted\n", state->numPoly);

    if(verbose) fprintf(stderr,"Rendering ");

    for(j=0; j<display->yres; j++) {

        /* generate scanline data */
        computeScanline((double)j, xsamples*ysamples, rx, ry, i0, i1, nup, scanline, proj);

        for(i=0; i<display->xres; i++) {
        
            /* initialize sample data */
	    rgba surfcol = color(0, 0, 0, 0);

	    /* this is the level where threading should probably occur */
            for(k=0; k<xsamples*ysamples; k++) { 

	        /* bypass if no polygons are visible */
	        if(scanline[i][k] != -1) {
        
	            /* check crop window boundaries */
	            if (((double)j/(display->yres-1) >= (1.-(display->cropWindow.bottom))) && 
	                ((double)j/(display->yres-1) <= (1.-(display->cropWindow.top)))  &&
	                ((double)i/(display->xres-1) >= (display->cropWindow.left)) && 
	                ((double)i/(display->xres-1) <= (display->cropWindow.right))) {
                                
		        /* map into uvw space (camera projection) */
                        r.d = (au + (bu - au) * (i + rx[k]) / display->xres) * u;
                        r.d = r.d + (av + (bv - av) * (j + ry[k]) / display->yres) * v;
                        r.d = r.d + (-s * w);
                
		        /* shade pixel */
		        //surfcol = surfcol + rw[k] * trace(r, raydepth);
	                surfcol = surfcol + rw[k] * scan(scanline[i][k], r, raydepth);
	                
			if(verbose && !(progress%10000)) fprintf(stderr,".");
			progress += 1;
	            }
	        }
            }

            /* quantize float data */
	    surfcol = quantize(surfcol, DITHER, one, blackpoint, whitepoint);
            rbuf[j][i] = (int)(surfcol.r + 0.5);
            gbuf[j][i] = (int)(surfcol.g + 0.5);
            bbuf[j][i] = (int)(surfcol.b + 0.5);
            abuf[j][i] = (int)(surfcol.a + 0.5);
	}

	ix += display->yres;
        randomSamples(xsamples, ysamples, rx, ry, rw, ix);

    }

    if(verbose) fprintf(stderr,"\n");

    /* write out image */
    rgbWrite(outfile, rbuf, gbuf, bbuf, abuf, display->xres, display->yres, 4, nbytes, blackpoint, whitepoint);

    exit(1);
}





