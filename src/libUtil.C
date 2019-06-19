#include "libUtil.h"

/* clamp */
double clamp(double a, double min, double max) {
    double b;

    if(a < min) b = min;
    else if(a > max) b = max;
    else b = a;

    return b;
}

/* dot product */
double dotp (vec3 a, vec3 b) {
    double c;
    c = a.x * b.x + a.y * b.y + a.z * b.z;
    return c;
}

/* cross product */
vec3 cross(vec3 a, vec3 b) {
    vec3 c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

/* magnitude */
double length(vec3 a) {
    double mag;
    mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return mag;
}

/* normalize */
vec3 normalize(vec3 b) {
    double mag;
    vec3 c;
    mag = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
    c.x = b.x/mag;
    c.y = b.y/mag;
    c.z = b.z/mag;
    return c;
}

/* set point */
vec3 point(double x, double y, double z) {
    vec3 a;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

/* scalar multiplication */
vec3 operator * (double a, vec3 b) {
    vec3 c;
    c.x = a * b.x;
    c.y = a * b.y;
    c.z = a * b.z;
    return c;
}

vec3 operator * (vec3 b, double a) {
    vec3 c;
    c.x = a * b.x;
    c.y = a * b.y;
    c.z = a * b.z;
    return c;
}

/* scalar division */
vec3 operator / (double a, vec3 b) {
    vec3 c;
    c.x = a / b.x;
    c.y = a / b.y;
    c.z = a / b.z;
    return c;
}

vec3 operator / (vec3 b, double a) {
    vec3 c;
    c.x = a / b.x;
    c.y = a / b.y;
    c.z = a / b.z;
    return c;
}

/* addition */
vec3 operator + (vec3 a, vec3 b) {
    vec3 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}

/* subtraction */
vec3 operator - (vec3 a, vec3 b) {
    vec3 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

/* equality */
int operator == (vec3 a, vec3 b) {
    if(a.x == b.x && a.y == b.y && a.z == b.z) return 1;
    else return 0;
}

/* set color */
rgba color(double r, double g, double b, double a) {
    rgba c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

/* scalar multiplication */
rgba operator * (double a, rgba b) {
    rgba c;
    c.r = a * b.r;
    c.g = a * b.g;
    c.b = a * b.b;
    c.a = a * b.a;
    return c;
}

rgba operator * (rgba b, double a) {
    rgba c;
    c.r = a * b.r;
    c.g = a * b.g;
    c.b = a * b.b;
    c.a = a * b.a;
    return c;
}

/* multiplication */
rgba operator * (rgba a, rgba b) {
    rgba c;
    c.r = a.r * b.r;
    c.g = a.g * b.g;
    c.b = a.b * b.b;
    c.a = a.a * b.a;
    return c;
}

/* scalar division */
rgba operator / (double a, rgba b) {
    rgba c;
    c.r = a / b.r;
    c.g = a / b.g;
    c.b = a / b.b;
    c.a = a / b.a;
    return c;
}

rgba operator / (rgba b, double a) {
    rgba c;
    c.r = a / b.r;
    c.g = a / b.g;
    c.b = a / b.b;
    c.a = a / b.a;
    return c;
}

/* addition */
rgba operator + (rgba a, rgba b) {
    rgba c;
    c.r = a.r + b.r;
    c.g = a.g + b.g;
    c.b = a.b + b.b;
    c.a = a.a + b.a;
    return c;
}

/* subtraction */
rgba operator - (rgba a, rgba b) {
    rgba c;
    c.r = a.r - b.r;
    c.g = a.g - b.g;
    c.b = a.b - b.b;
    c.a = a.a - b.a;
    return c;
}

/* gamma */
rgba cgamma(rgba a, double b) {
    rgba c;
    c.r = pow(a.r, b);
    c.g = pow(a.g, b);
    c.b = pow(a.b, b);
    c.a = pow(a.a, b);
    return c;
}

/* clamp */
rgba clamp(rgba a, double min, double max) {
    rgba b;

    if(a.r < min) b.r = min;
    else if(a.r > max) b.r = max;
    else b.r = a.r;

    if(a.g < min) b.g = min;
    else if(a.g > max) b.g = max;
    else b.g = a.g;

    if(a.b < min) b.b = min;
    else if(a.b > max) b.b = max;
    else b.b = a.b;

    if(a.a < min) b.a = min;
    else if(a.a > max) b.a = max;
    else b.a = a.a;

    return b;
}

/* reflect */
vec3 reflect(vec3 d, vec3 n) {
    vec3 r, a;

    a = (-2.0 * dotp(d, n)) * n;
    r = d + a;

    return r;
}

/* refract */
vec3 refract(double eta, vec3 d, vec3 n) {
    vec3 r, t;
    double c1, c2s;

    c1 = -1. * dotp(d, n);
    c2s = 1. - eta * eta * (1 - c1 * c1);

    if(c2s < 0.)  {
        r = reflect(d, n);
        return r;
    }
    else  {
        t = (eta * d) + (eta * c1 - sqrt(c2s)) * n;
        return t;
    }

}

/* orient vector towards camera */
vec3 faceForward(vec3 n, vec3 d) {
    vec3 nf;

    if(dotp(n, d) > 0) {
        nf = -1.0 * n;
    }
    else {
        nf = n;
    }

    return nf;
}

/* identity matrix */
void identity(mat4x4 *a) {
    int i, j;

    for(j=0; j<4; j++) {
        for(i=0; i<4; i++) {
            a->element[i][j] = (i == j) ? 1 : 0;
        }
    }
}

/* set matrix */
void mset(mat4x4 *a, mat4x4 *b) {
    int i, j;

    for(j=0; j<4; j++) {
        for(i=0; i<4; i++) {
            a->element[i][j] = b->element[i][j];
        }
    }
}

/* matrix scalar multiplication */
void mscalar(mat4x4 *a, double b, mat4x4 *c) {
    int i, j;

    for(j=0; j<4; j++) {
        for(i=0; i<4; i++) {
            a->element[i][j] = b * c->element[i][j];
        }
    }
}

/* matrix multiplication */
void mmult(mat4x4 *a, mat4x4 *b, mat4x4 *c) {
    int i, j, k;

    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
	    a->element[i][j] = 0;
            for(k=0; k<4; k++) {
                a->element[i][j] += b->element[i][k] * c->element[k][j];
            }
        }
    }
}

/* determinant of a 2x2 matrix */
double det2x2(double a, double b, double c, double d) {
    double ans;
    ans = a * d - b * c;
    return ans;
}

/* determinant of a 3x3 matrix */
double det3x3(double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3) {
    double ans;

    ans = a1 * det2x2(b2, b3, c2, c3) - b1 * det2x2(a2, a3, c2, c3) + c1 * det2x2(a2, a3, b2, b3);

    return ans;
}

/* determinant of a 4x4 matrix */
double det4x4(mat4x4 *a) {
    double ans;
    double a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

    a1 = a->element[0][0]; b1 = a->element[0][1]; c1 = a->element[0][2]; d1 = a->element[0][3];
    a2 = a->element[1][0]; b2 = a->element[1][1]; c2 = a->element[1][2]; d2 = a->element[1][3];
    a3 = a->element[2][0]; b3 = a->element[2][1]; c3 = a->element[2][2]; d3 = a->element[2][3];
    a4 = a->element[3][0]; b4 = a->element[3][1]; c4 = a->element[3][2]; d4 = a->element[3][3];

    ans = a1 * det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4) - 
	  b1 * det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4) +
	  c1 * det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4) -
	  d1 * det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

    return ans;
}

/* adjoint of matrix */
void adjoint(mat4x4 *a, mat4x4 *b) {
    double a1, a2, a3, a4, b1, b2, b3, b4;
    double c1, c2, c3, c4, d1, d2, d3, d4;

    a1 = a->element[0][0]; b1 = a->element[0][1]; c1 = a->element[0][2]; d1 = a->element[0][3];
    a2 = a->element[1][0]; b2 = a->element[1][1]; c2 = a->element[1][2]; d2 = a->element[1][3];
    a3 = a->element[2][0]; b3 = a->element[2][1]; c3 = a->element[2][2]; d3 = a->element[2][3];
    a4 = a->element[3][0]; b4 = a->element[3][1]; c4 = a->element[3][2]; d4 = a->element[3][3];

    b->element[0][0] = det3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
    b->element[1][0] = -det3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
    b->element[2][0] = det3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
    b->element[3][0] = -det3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

    b->element[0][1] = det3x3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
    b->element[1][1] = -det3x3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
    b->element[2][1] = det3x3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
    b->element[3][1] = -det3x3(a1, a3, a4, b1, b3, b4, c1, c3, c4);

    b->element[0][2] = det3x3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
    b->element[1][2] = -det3x3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
    b->element[2][2] = det3x3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
    b->element[3][2] = -det3x3(a1, a2, a4, b1, b2, b4, c1, c2, c4);

    b->element[0][3] = det3x3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
    b->element[1][3] = -det3x3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
    b->element[2][3] = det3x3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
    b->element[3][3] = -det3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

/* inverse of matrix */
void inverse(mat4x4 *a, mat4x4 *b) {
    int i, j;
    double det;

    adjoint(a, b);

    det = det4x4(b);

    if(fabs(det) < EPS) {
	printf("Non-singular matrix, no inverse!\n");
	exit(0);
    }

    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
	    b->element[i][j] = b->element[i][j] / det;
}

/* transform coordinates */
vec3 transform(vec3 xi, mat4x4 *a) {
    vec3 xo;
    double w;

    w = xi.x * a->element[0][3] + xi.y * a->element[1][3]+ xi.z * a->element[2][3] + a->element[3][3];
    xo.x = xi.x * a->element[0][0] + xi.y * a->element[1][0]+ xi.z * a->element[2][0] + a->element[3][0];
    xo.y = xi.x * a->element[0][1] + xi.y * a->element[1][1]+ xi.z * a->element[2][1] + a->element[3][1];
    xo.z = xi.x * a->element[0][2] + xi.y * a->element[1][2]+ xi.z * a->element[2][2] + a->element[3][2];

    if(w != 0) {
	xo.x /= w;
	xo.y /= w;
	xo.z /= w;
    }

    return xo;
}

/* translate coordinates */
vec3 translate(vec3 xi, vec3 trans) {
    vec3 xo;

    xo.x = xi.x + trans.x;
    xo.y = xi.y + trans.y;
    xo.z = xi.z + trans.z;

    return xo;
}


/* rotate coordinates */
vec3 rotate(vec3 xi, double angle, int axis) {
    vec3 xo;
    mat4x4 *a;

    identity(a);

    if(axis == 0) {
	a->element[1][1] = cos(angle);
	a->element[1][2] = -sin(angle);
	a->element[2][1] = sin(angle);
	a->element[2][2] = cos(angle);
    }
    else if(axis == 1) {
	a->element[0][0] = cos(angle);
	a->element[0][2] = sin(angle);
	a->element[2][0] = -sin(angle);
	a->element[2][2] = cos(angle);
    }
    else {
	a->element[0][0] = cos(angle);
	a->element[0][1] = -sin(angle);
	a->element[1][0] = sin(angle);
	a->element[1][1] = cos(angle);
    }

    xo = transform(xi, a);

    return xo;
}

/* load poly file */
void getPolyCount(char *filename, int *np, int *nv) {
    char *sptr;
    char str[SMALLBUFFER];
    char ret0[SMALLBUFFER];
    FILE *fd;
    int polys, points;

    /* scan to determine number of polygons */
    if(!(fd = fopen(filename, "r"))) {
        fprintf(stderr, "%s: File Not Found!\n", filename);
        return;
    }

    *np = 0;
    *nv = 0;
    polys = 0;
    while(1) {
	sptr = fgets(str, sizeof(str), fd);
	if(sptr == NULL) break;

	sscanf(str, "%s", ret0);

	if(!strcmp(ret0, "END")) {
	    break;
	}

	if(polys) {
	    *np += 1;
	}

	if(!strcmp(ret0, "POLYS")) {
	    points = 0;
	    polys = 1;
	}

	if(points) {
	    *nv += 1;
	}

	if(!strcmp(ret0, "POINTS")) {
	    points = 1;
	    polys = 0;
	}
    }
    fclose(fd);
}

/* load poly file */
int loadPoly(char *filename, vec3 *vertices[3], vec3 *uvcoords[3], vec3 *vnorms[3], int np, int nv) {
    char *sptr, *ptr, *dup, *newcursor;
    char str[SMALLBUFFER];
    char ret0[SMALLBUFFER], ret1[SMALLBUFFER], ret2[SMALLBUFFER], ret3[SMALLBUFFER];
    FILE *fd;
    int i, j, n1, n2;
    triPoly *vlist;
    vec3 *tv, *tuv, *tvn;
    int points, polys;

    /* scan to determine number of polygons */
    if(!(fd = fopen(filename, "r"))) {
        fprintf(stderr, "%s: File Not Found!\n", filename);
        return(0);
    }

    tv = new vec3[nv];
    tuv = new vec3[nv];
    tvn = new vec3[nv];
    vlist = new triPoly[np];

    n1 = 0;
    n2 = 0;
    points = 0;
    polys = 0;
    sprintf(ret0, "");
    while(1) {
	sptr = fgets(str, sizeof(str), fd);
	if(sptr == NULL) break;
	dup = strdup(sptr);

	sscanf(str, "%s", ret0);

	if(!strcmp(ret0, "END")) {
	    free(dup);
	    break;
	}

	if(polys) {
	    sscanf(str, "%s%s%s%s", ret0, ret1, ret2, ret3);
	    vlist[n2].vert0 = atoi(ret1);
	    vlist[n2].vert1 = atoi(ret2);
	    vlist[n2].vert2 = atoi(ret3);
	    n2 += 1;
	}

	sscanf(str, "%s", ret0);

	if(!strcmp(ret0, "POLYS")) {
	    points = 0;
	    polys = 1;
	}

	if(points) {
	    newcursor = strtok(dup, " ");
	    while(newcursor) {
		if(match(newcursor, ":")) {
		    newcursor = strtok(NULL, ":");
	            sscanf(newcursor, "%s%s%s", ret0, ret1, ret2);
	            tv[n1].x = atof(ret0);
	            tv[n1].y = atof(ret1);
	            tv[n1].z = atof(ret2);
		}
                newcursor = strtok(NULL, " ");
	    }

	    dup = strdup(sptr);
	    newcursor = strtok(dup, " ");
	    while(newcursor) {
		if(match(newcursor, "n")) {
		    char *tmp1 = new char[strlen(newcursor)-3];
		}
                newcursor = strtok(NULL, " ");
	    }

	    //ptr = regcmp("([0-9.]+)$0", ", ", "([0-9.]+)$1", (char *)0);
	    //regex(ptr, dup, ret0, ret1);
	    //free(ptr);
	    //tuv[n1].x = atof(ret0);
	    //tuv[n1].y = atof(ret1);
	    //tuv[n1].z = 0;

	    dup = strdup(sptr);
	    ptr = regcmp("([0-9.-]+)$0", ", ", "([0-9.-]+)$1", ", ", "([0-9.-]+)$2", (char *)0);
	    regex(ptr, dup, ret0, ret1, ret2);
	    free(ptr);
	    tvn[n1].x = atof(ret0);
	    tvn[n1].y = atof(ret1);
	    tvn[n1].z = atof(ret2);

	    n1 += 1;
	}

	sscanf(str, "%s", ret0);

	if(!strcmp(ret0, "POINTS")) {
	    points = 1;
	    polys = 0;
	}

	free(dup);
    }
    fclose(fd);

    /* determine ordered poly list */
    for(j=0; j<np; j++) {
        vertices[j][0].x = tv[vlist[j].vert0 - 1].x;
	vertices[j][0].y = tv[vlist[j].vert0 - 1].y;
	vertices[j][0].z = tv[vlist[j].vert0 - 1].z;
        vertices[j][1].x = tv[vlist[j].vert1 - 1].x;
	vertices[j][1].y = tv[vlist[j].vert1 - 1].y;
	vertices[j][1].z = tv[vlist[j].vert1 - 1].z;
        vertices[j][2].x = tv[vlist[j].vert2 - 1].x;
	vertices[j][2].y = tv[vlist[j].vert2 - 1].y;
	vertices[j][2].z = tv[vlist[j].vert2 - 1].z;
        uvcoords[j][0].x = tuv[vlist[j].vert0 - 1].x;
	uvcoords[j][0].y = tuv[vlist[j].vert0 - 1].y;
	uvcoords[j][0].z = tuv[vlist[j].vert0 - 1].z;
        uvcoords[j][1].x = tuv[vlist[j].vert1 - 1].x;
	uvcoords[j][1].y = tuv[vlist[j].vert1 - 1].y;
	uvcoords[j][1].z = tuv[vlist[j].vert1 - 1].z;
        uvcoords[j][2].x = tuv[vlist[j].vert2 - 1].x;
	uvcoords[j][2].y = tuv[vlist[j].vert2 - 1].y;
	uvcoords[j][2].z = tuv[vlist[j].vert2 - 1].z;
        vnorms[j][0].x = tvn[vlist[j].vert0 - 1].x;
	vnorms[j][0].y = tvn[vlist[j].vert0 - 1].y;
	vnorms[j][0].z = tvn[vlist[j].vert0 - 1].z;
        vnorms[j][1].x = tvn[vlist[j].vert1 - 1].x;
	vnorms[j][1].y = tvn[vlist[j].vert1 - 1].y;
	vnorms[j][1].z = tvn[vlist[j].vert1 - 1].z;
        vnorms[j][2].x = tvn[vlist[j].vert2 - 1].x;
	vnorms[j][2].y = tvn[vlist[j].vert2 - 1].y;
	vnorms[j][2].z = tvn[vlist[j].vert2 - 1].z;
    }

    delete [] tv;
    delete [] tuv;
    delete [] tvn;
    delete [] vlist;

    return(1);
}

/* jittering a regular grid */
void randomSamples(int xsamples, int ysamples, double *rx, double *ry, double *rw, long seed) {
    int i, j, k;
    double x0, y0;

    srand48(seed);
    k = 0;
    if(xsamples == 1 && ysamples == 1) {
        y0 = 0.5;
        x0 = 0.5;
        rx[0] = x0;
        ry[0] = y0;
        rw[0] = 1.;
    } 
    else {
        y0 = 0.5 / ysamples;
        for(j=0; j<ysamples; j++) { 
	    x0 = 0.5 / xsamples;
            for(i=0; i<xsamples; i++) { 
                rx[k] = x0 + (drand48() - 0.5) / xsamples;
                ry[k] = y0 + (drand48() - 0.5) / ysamples;
                rw[k] = 1. / (xsamples * ysamples);
		x0 += 1.0 / xsamples;
		k += 1;
            }
	    y0 += 1.0 / ysamples;
        }
    }
}

double radians(double angle) {
    double rad;
    rad = angle * PI / 180.;
    return rad;
}

/* transform point into raster space */
vec3 toRaster(vec3 p, mat4x4 *c, double fov, sw screenWindow) {
    vec3 pcam, s;
    double scale, focalLength, aspect;

    pcam = transform(p, c);
    focalLength = 1.0 / tan(fov/2.);
    scale = focalLength / pcam.z;
 
    s.x = (scale * pcam.x - screenWindow.xmin) / (screenWindow.xmax - screenWindow.xmin);
    s.y = (scale * pcam.y - screenWindow.ymin) / (screenWindow.ymax - screenWindow.ymin);
    s.z = pcam.z;
 
    return s;
}

/* push entry to top of stack */
void push(int entry, int n, int *stack) {
    int i;

    assert(stack != NULL);

    for(i=n-1; i>=1; i--) {
	stack[i] = stack[i-1];
    }
    stack[0] = entry;
}

int match(const char *string, char *pattern) {
    int status;
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0){
        return(0);      /* report error */
    }
    
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return(0);      /* report error */
    }
    return(1);
}

rgba quantize(rgba surfcol, double dither, int one, int blackpoint, int whitepoint) {
    rgba col;

    col.r = one * surfcol.r + dither * drand48();
    col.g = one * surfcol.g + dither * drand48();
    col.b = one * surfcol.b + dither * drand48();
    col.a = one * surfcol.a;
    col = col;
    col = clamp(col, blackpoint, whitepoint);

    return col;
}

/* smoothstep (hermite interpolation) */
double smoothstep(double in, double out, double val) {
    double nuval;

    if(val < in) return(0.);
    else if(val > out) return(1.);

    nuval = (val - in)/(out - in);
    nuval = -2.*nuval*nuval*nuval + 3*nuval*nuval;

    return nuval;
}


