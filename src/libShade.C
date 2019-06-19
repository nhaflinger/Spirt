#include "libShade.h"


/* find closest point */
int findClosestPoint(ray r, vec3 *p, int *m, int *np, double *t) {
    int mx, h, hit;
    double t0, t1;
    vec3 pc;

    hit = 0;
    t0 = INF;
    for(mx=0; mx<state->numProcs; mx++) {
        /* find intersection */
        h = procs[mx]->primIntersection(r, t);
	pc = r.o + (*t) * r.d;
        t1 = *t;

        if(h && t1<=t0) {
	    hit = h;
            *m = mx;
            *p = pc;
            t0 = t1;
        }
    }
    return hit;
}

/* is point in shadow? */
int rayShadow(ray rs, vec3 pp, rgba *color, int depth) {
    int j, k, m, hit, shad, np, npoly;
    vec3 p, lp, ld, n;
    double t, trans;

    /* check if last object hit casts shadow */
    hit = procs[state->lastRayShadowHit]->primIntersection(rs, &t);

    if(hit) {
        lp = p - rs.o;

        shad = 0;
    
        lp = p - rs.o;
        ld = pp - rs.o;
    
        if(length(lp) < length(ld)) shad = 1;
    
        // compute shadow color
        procs[m]->primNormal(p, &n);
        *color = surfaceShader(m, rs, p, n, depth);
    
        return shad;
    }

    hit = findClosestPoint(rs, &p, &m, &np, &t);
    if(!hit) return 0;

    lp = p - rs.o;

    shad = 0;

    lp = p - rs.o;
    ld = pp - rs.o;

    if(length(lp) < length(ld)) shad = 1;

    // compute shadow color
    procs[m]->primNormal(p, &n);
    *color = surfaceShader(m, rs, p, n, depth);

    return shad;
}

/* compute glossy reflection */
rgba getGlossyReflection(double glossiness, double reflectivity, ray r, vec3 nf, int n, int depth) {
    rgba reflcol, surfcol;
    FloatLong seed;
    double phi, theta, sa;
    double r1, r2, r3;
    vec3 rt, a, ap, u, v, w, t;

    surfcol = color(0, 0, 0, 0);
    depth += 1;
    seed.f = r.o.x + r.o.y + r.o.z;
    srand48(seed.l);

    /* shoot n random rays about mirror direction */
    /* secondary rays should obey same rule as specular falloff */
    /* purely random rays are too noisy so I need some sort */
    /* of stratified sampling scheme for secondary rays */
    for(int i=0; i<n; i++) {
	if(n == 1) {
            reflcol = reflectivity * trace(r, depth);
            surfcol = surfcol + reflcol;
	} 
	else {
	    r1 = drand48();
	    r2 = drand48();
	    /* I'm kinda guessing here as to what this should look like ;) */
	    theta = acos(sqrt(r1));
	    theta = pow(1. - (2. * theta / PI), 1. / glossiness) * theta;
	    phi = r2 * 2. * PI;
    
	    a = point(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
	    w = normalize(r.d);
	    t = point(w.x, w.y, w.z);
        
	    /* find primary axis */
	    if((fabs(t.x) < fabs(t.y)) && (fabs(t.x) < fabs(t.z))) t.x = 1;
	    else if((fabs(t.y) < fabs(t.x)) && (fabs(t.y) < fabs(t.z))) t.y = 1;
	    else if((fabs(t.z) < fabs(t.x)) && (fabs(t.z) < fabs(t.y))) t.z = 1;
       
	    u = normalize(cross(t, w));
	    v = cross(w, u);
        
	    /* rotate vector a */
	    ap.x = a.x * u.x + a.y * v.x + a.z * w.x;
	    ap.y = a.x * u.y + a.y * v.y + a.z * w.y;
	    ap.z = a.x * u.z + a.y * v.z + a.z * w.z;

	    /* do not consider rays outside hemisphere */
	    /* add in some Russian roulette */
	    r3 = drand48();
	    if((dotp(ap, nf) <= 0) && (r3 > reflectivity)) {
		n -= 1;
	    }
            else {
                r.d = point(ap.x, ap.y, ap.z);
                reflcol = reflectivity * trace(r, depth);
                surfcol = surfcol + reflcol;
	    }
	}
    }
    surfcol = (1./n) * surfcol;

    return surfcol;
}

/* compute diffuse illumination */
rgba getDiffuse(vec3 n, vec3 p, int depth) {
    int i, j, shad;
    rgba col, diffuse, lgtcol; 
    vec3 pp, ld;
    ray rs;
    FloatLong seed;
    mat4x4 *lt;
    
    col = color(BACKGROUND, BACKGROUND, BACKGROUND, 1);
    diffuse = color(BACKGROUND, BACKGROUND, BACKGROUND, BACKGROUND);
    
    ILLUMINANCE(i) {
        lgtcol = color(0, 0, 0, 0);

        /* light direction */
        lt = lgts[i]->getLgtPrim()->getTransform();

        if(!strcmp(lgts[i]->getLgtPrim()->getType(), "area")) {
	    seed.f = p.x + p.y + p.z;
	    srand48(seed.l);

	    int samples = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getNumSamples();
            double width = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getWidth();
            double height = ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getHeight();

	    for(j=0; j<samples; j++) {
	        /* Pick random point on light */
		if(samples <= 1) {
		    pp = point(0, 0, 0);
		}
		else {
		    pp = point((0.5 - drand48()) * width, 0, (0.5 - drand48()) * height);
		}

                pp = transform(pp, lt);
                ld = pp - p;

                /* in shadow? */
                if(dotp(n, ld) > 0) {
                    rs.o = p;
                    rs.d = ld;

		    /* does this light cast shadows? */
		    rgba shadColor = color(0, 0, 0, 0);
		    if(lgts[i]->getLgtPrim()->getCastShadow()) shad = rayShadow(rs, pp, &shadColor, depth);
		    else shad = 0;
        
                    if(!shad) {
			lgtcol = lightShader(i, p);
		    }
		    else {
			lgtcol = color(shadColor.r, shadColor.g, shadColor.b, shadColor.a);
		    }
                }
            
                diffuse = dotp(n, normalize(ld)) * lgtcol;

		/*  clamp colors */
	        diffuse = clamp(diffuse, 0, 1);

                col = col + diffuse;
	    }
	    col = (1./((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getNumSamples()) *  col;
	    col = (((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getWidth() * ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getHeight()) * col;
	}
        else {
	    pp = point(0, 0, 0);

            pp = transform(pp, lt);
            ld = pp - p;

            /* in shadow? */
            if(dotp(n, ld) > 0) {
                rs.o = p;
                rs.d = ld;

		/* does this light cast shadows? */
		rgba shadColor = color(0, 0, 0, 0);
		if(lgts[i]->getLgtPrim()->getCastShadow()) shad = rayShadow(rs, pp, &shadColor, depth);
		else shad = 0;
        
                if(!shad) {
		    lgtcol = lightShader(i, p);
                } 
		else {
		    lgtcol = color(shadColor.r, shadColor.g, shadColor.b, shadColor.a);
		}
            }

            diffuse = dotp(n, normalize(ld)) * lgtcol;
        
	    /*  clamp colors */
	    diffuse = clamp(diffuse, 0, 1);
                            
            col = col + diffuse;
	}
    }
    
    return col;
}

/* compute specular illumination */
rgba getSpecular(vec3 n, vec3 p, double ns, int depth) {
    int i, shad;
    rgba col, specular, lgtcol; 
    vec3 pp, ld, half, viewpnt, viewdir;
    ray rs;
    mat4x4 *lt;

    col = color(BACKGROUND, BACKGROUND, BACKGROUND, 0);
    specular = color(BACKGROUND, BACKGROUND, BACKGROUND, BACKGROUND);
    
    viewpnt = cameras[0].getViewPoint();
    viewdir = viewpnt - p;

    ILLUMINANCE(i) {
	lgtcol = color(0, 0, 0, 0);
        
        /* light direction */
        lt = lgts[i]->getLgtPrim()->getTransform();
        pp = point(lt->element[3][0], lt->element[3][1], lt->element[3][2]);
        ld = pp - p;

	half = normalize(normalize(viewdir) + normalize(ld));

        if(!strcmp(lgts[i]->getLgtPrim()->getType(), "area")) {
            /* in shadow? */
            if(dotp(n, ld) > 0) {
                rs.o = p;
                rs.d = ld;
    
	        /* does this light cast shadows? */
		rgba shadColor = color(0, 0, 0, 0);
	        if(lgts[i]->getLgtPrim()->getCastShadow()) shad = rayShadow(rs, pp, &shadColor, depth);
	        else shad = 0;
    
                if(!shad) {
		    lgtcol = lightShader(i, p);
                } 
		else {
		    lgtcol = color(shadColor.r, shadColor.g, shadColor.b, shadColor.a);
		}
            }

            lgtcol = (((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getWidth() * ((DT_AreaLgtPrim *)lgts[i]->getLgtPrim())->getHeight()) * lgtcol;
        }
	else {
            /* in shadow? */
            if(dotp(n, ld) > 0) {
                rs.o = p;
                rs.d = ld;
    
	        /* does this light cast shadows? */
		rgba shadColor = color(0, 0, 0, 0);
	        if(lgts[i]->getLgtPrim()->getCastShadow()) shad = rayShadow(rs, pp, &shadColor, depth);
	        else shad = 0;
    
                if(!shad) {
		    lgtcol = lightShader(i, p);
                } 
		else {
		    lgtcol = color(shadColor.r, shadColor.g, shadColor.b, shadColor.a);
		}
            }
	}

        specular = pow(dotp(n, normalize(half)), 1./ns) * lgtcol;
	specular.a = 0;

	/*  clamp colors */
	specular = clamp(specular, 0, 1);
                            
        col = col + specular;
    }

    return col;
}

/* trace ray */
rgba trace(ray r, int depth) {
    int hit, h, m, i, np;
    vec3 p, n, pc, nc;
    double t, d0, d1;

    /* find closest point */
    hit = findClosestPoint(r, &p, &m, &np, &t);

    if(hit) {
        procs[m]->primNormal(p, &n);
	return surfaceShader(m, r, p, n, depth);
    }
    else {
        return color(BACKGROUND, BACKGROUND, BACKGROUND, BACKGROUND);
    }
}

/* determine final color */
rgba surfaceShader(int m, ray r, vec3 p, vec3 n, int depth) {
    rgba surfcol;
    void *library;
    shader theShader;
    const char *error;
    char path[LARGEBUFFER];

    sprintf(path, "%s.so", procs[m]->getPrim()->getShader());

    library = dlopen(path, RTLD_NOW);

    if(library == NULL) {
	fprintf(stderr, "Could not open library %s (error: %s)\n", path, dlerror());
    }

    dlerror();
    theShader = (shader)dlsym(library, "surfaceColor");
    error = dlerror();

    if(error) {
	fprintf(stderr, "Could not find surfaceColor function (error: %s)\n", error);
    }

    surfcol = (*theShader)(m, r, p, n, depth);

    return surfcol;
}

/* determine light color */
rgba lightShader(int i, vec3 p) {
    rgba lgtcol;
    void *library;
    lgtshader theShader;
    const char *error;
    char path[LARGEBUFFER];

    sprintf(path, "%s.so", lgts[i]->getLgtPrim()->getShader());

    library = dlopen(path, RTLD_NOW);

    if(library == NULL) {
	fprintf(stderr, "Could not open library %s (error: %s)\n", path, dlerror());
    }

    dlerror();
    theShader = (lgtshader)dlsym(library, "lightColor");
    error = dlerror();

    if(error) {
	fprintf(stderr, "Could not find lightColor function (error: %s)\n", error);
    }

    lgtcol = (*theShader)(i, p);

    return lgtcol;
}


/* sort polygons */
void sortPolygons(extents2D *ex, vec3 **nup) {
    /* get camera info */
    mat4x4 *ct = cameras[0].getTransform();
    double fov = 2. * atan(0.5 * cameras[0].getAperture() / cameras[0].getFocal());
    dsp *display = cameras[0].getDisplay();

    int i = 0;
    for(int m=0; m<state->numProcs; m++) {
        if(procs[m]->primType() == POLYGON) {
	    /* project points into raster space */
            vec3 *points = ((DT_PolyPrim *)procs[m]->getPrim())->getPoints();

            vec3 norm;
	    norm = normalize(cross(points[1] - points[0], points[2] - points[1]));

            nup[i][0] = toRaster(points[0], ct, fov, display->screenWindow);
            nup[i][1] = toRaster(points[1], ct, fov, display->screenWindow);
            nup[i][2] = toRaster(points[2], ct, fov, display->screenWindow);
            
	    /* determine extents */
	    double ymin = MIN(nup[i][0].y, nup[i][1].y);
	    ymin = MIN(ymin, nup[i][2].y);
	    double ymax = MAX(nup[i][0].y, nup[i][1].y);
            ymax = MAX(ymax, nup[i][2].y);

	    double xmin = MIN(nup[i][0].x, nup[i][1].x);
	    xmin = MIN(xmin, nup[i][2].x);
	    double xmax = MAX(nup[i][0].x, nup[i][1].x);
            xmax = MAX(xmax, nup[i][2].x);

            ex[i].xmin = (int)floor(xmin * display->xres);
            ex[i].xmax = (int)ceil(xmax * display->xres);
            ex[i].ymin = (int)floor(ymin * display->yres);
            ex[i].ymax = (int)ceil(ymax * display->yres);

	    i += 1;
        }
    }

}

/* compute polygons visible in this scan-line */
void computeScanline(double line, int samples, double *rx, double *ry, extents2D *ex, vec3 *nup[3], int **scanline, prj *proj) {
    int i, j, k, l, m, nv;
    vec3 viewpnt, viewdir;

    /* get camera info */
    dsp *display = cameras[0].getDisplay();
    viewpnt = cameras[0].getViewPoint();
    viewdir = cameras[0].getViewDirection();

    double du = (proj->bu - proj->au) / display->xres;
    double dv = (proj->bv - proj->av) / display->yres;

    double zdepth[display->xres][samples];
    /* initialize scanline and zdepth buffer */
    for(i=0; i<display->xres; i++) {
        for(k=0; k<samples; k++) {
            scanline[i][k] = -1;
	    zdepth[i][k] = INF;
        }
    }

    nv = 3;

    /* for each polygon find which pixels it lies in */
    for(k=0; k<samples; k++) {
        i = 0;
        for(m=0; m<state->numProcs; m++) {
            if(procs[m]->primType() == POLYGON) {
    
	        if((line+ry[k]) >= ex[i].ymin && (line+ry[k]) <= ex[i].ymax) {
    
	            double xmin = (double)display->xres;
		    double xmax = 0;
    
	            for(l=0; l<nv; l++) {
		        double y1 = nup[i][l].y * display->yres;
		        double y2 = nup[i][(l+1)%nv].y * display->yres;
		        if(y1 < (line+ry[k]) && y2 < (line+ry[k])) continue;
		        if(y1 > (line+ry[k]) && y2 > (line+ry[k])) continue;
		        double dely = y2 - y1;
		        if(fabs(dely) < EPS) continue;
		        double delx = (nup[i][(l+1)%nv].x - nup[i][l].x) * display->xres;
		        double xint = nup[i][l].x * display->xres + ((line+ry[k]) - y1) * delx / dely;
		        if(xint < xmin) xmin = xint;
		        if(xint > xmax) xmax = xint;
		    }
    
		    /* check visibility */
                    double rem1 = xmin - (int)xmin;
                    double rem2 = xmax - (int)xmax;
                    if(rx[k] < rem1) xmin = ceil(xmin);
                    if(rx[k] > rem2) xmax = floor(xmax);

		    xmin = clamp(floor(xmin), 0, (double)display->xres - 1);
		    xmax = clamp(ceil(xmax), 0, (double)display->xres - 1);
    
	            /* assign polygon to pixel */
		    for(l=(int)xmin; l<(int)xmax; l++) {
		        /* compute zdepth */
		        vec3 p;
		        double t;
		        ray r;
        
		        r.o = viewpnt;
		        r.d = viewdir;
    
                        /* map into uvw space (camera projection) */
		        r.d = (proj->au + du * l) * proj->u;
		        r.d = r.d + (proj->av + dv * (line+ry[k])) * proj->v;
		        r.d = r.d + -1 * proj->s * proj->w;
        
                        procs[m]->primIntersection(r, &t);
                        p = r.o + t * r.d;
        
		        if(length(p) < zdepth[l][k]) {
		            zdepth[l][k] = length(p);
		            scanline[l][k] = m;
		        }
		    }
                }
    
	        i += 1;
            } 
        }
    }
}

/* find intersection */
rgba scan(int prim, ray r, int raydepth) {
    vec3 p, n;
    double t;
    int hit;
    
    hit = procs[prim]->primIntersection(r, &t);
    p = r.o + t * r.d;

    if(hit) {
        procs[prim]->primNormal(p, &n);
        return surfaceShader(prim, r, p, n, raydepth);
    }
    else {
        return color(BACKGROUND, BACKGROUND, BACKGROUND, BACKGROUND);
    }
}

