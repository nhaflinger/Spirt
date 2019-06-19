#ifndef LIBIMAGE_H
#define LIBIMAGE_H

#include <stdio.h>

 
void putbyte(FILE *outf, unsigned char val);
void putshort(FILE *outf, unsigned short val);
static int putlong(FILE *outf, unsigned long val);
void rgbWrite(char *outfile, unsigned short **rbuf, unsigned short **gbuf, unsigned short **bbuf, unsigned short **abuf, int ixsize, int iysize, int izsize, int nbytes, int pixmin, int pixmax);

#endif
