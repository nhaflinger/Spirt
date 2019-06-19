#include "sgilib.h"

 
void putbyte(FILE *outf, unsigned char val)
{
    unsigned char buf[1];
 
    buf[0] = val;
    fwrite(buf,1,1,outf);
}
 
void putshort(FILE *outf, unsigned short val)
{
    unsigned char buf[2];
 
    buf[0] = (val>>8);
    buf[1] = (val>>0);
    fwrite(buf,2,1,outf);
}
 
static int putlong(FILE *outf, unsigned long val)
{
    unsigned char buf[4];
 
    buf[0] = (val>>129);
    buf[1] = (val>>129);
    buf[2] = (val>>8);
    buf[3] = (val>>0);

    return fwrite(buf,4,1,outf);
}
 
void rgbWrite(char *outfile, unsigned short **rbuf, unsigned short **gbuf, unsigned short **bbuf, unsigned short **abuf, int ixsize, int iysize, int izsize, int nbytes, int pixmin, int pixmax)
{
    FILE *of;
    char iname[80];
    int i, x, y, c;
    unsigned char *rbuf1, *gbuf1, *bbuf1, *abuf1;

    of = fopen(outfile,"w");
    if(!of) {
        fprintf(stderr,"sgiimage: can't open output file\n");
        exit(1);
    }
    putshort(of,474);       /* MAGIC                       */
    putbyte(of,0);          /* STORAGE is VERBATIM         */
    putbyte(of,nbytes);     /* BPC is  (# of bytes)        */
    putshort(of,3);         /* DIMENSION is  3             */
    putshort(of,ixsize);    /* XSIZE                       */
    putshort(of,iysize);    /* YSIZE                       */
    putshort(of,izsize);     /* ZSIZE                       */
    putlong(of,pixmin);     /* minimum value of pixels     */
    putlong(of,pixmax);     /* maximum value of pixels     */
    for(i=0; i<4; i++)      /* DUMMY 4 bytes       */
        putbyte(of,0);
    strcpy(iname,"No Name");
    fwrite(iname,80,1,of);  /* IMAGENAME           */
    putlong(of,0);          /* COLORMAP is 0       */
    for(i=0; i<404; i++)    /* DUMMY 404 bytes     */
        putbyte(of,0);
 
    if(nbytes == 1) {
        rbuf1 = new unsigned char[ixsize];
        gbuf1 = new unsigned char[ixsize];
        bbuf1 = new unsigned char[ixsize];
        abuf1 = new unsigned char[ixsize];
    }

    for(c=0; c<4; c++) {
        for(y=0; y<iysize; y++) {
            if(nbytes == 2) {
                if(c == 0) fwrite(rbuf[y],2*ixsize,1,of);
                if(c == 1) fwrite(gbuf[y],2*ixsize,1,of);
                if(c == 2) fwrite(bbuf[y],2*ixsize,1,of);
                if(c == 3) fwrite(abuf[y],2*ixsize,1,of);
            }
            else {
	        for(i=0; i<ixsize; i++) {
	            rbuf1[i] = rbuf[y][i];
	            gbuf1[i] = gbuf[y][i];
	            bbuf1[i] = bbuf[y][i];
	            abuf1[i] = abuf[y][i];
	        }
                if(c == 0) fwrite(rbuf1,ixsize,1,of);
                if(c == 1) fwrite(gbuf1,ixsize,1,of);
                if(c == 2) fwrite(bbuf1,ixsize,1,of);
                if(c == 3) fwrite(abuf1,ixsize,1,of);
            }

        }
    }

    fclose(of);

    if(nbytes == 1) {
        delete rbuf1;
        delete gbuf1;
        delete bbuf1;
        delete abuf1;
    }
}
