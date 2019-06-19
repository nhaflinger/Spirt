SRCDIR	= .

SHELL	= /bin/sh
NULL	=
CC	= /usr/bin/gcc
#
COPTS	= -g
OPTIMIZER=-O
IPATH	= -I${SRCDIR}
CFLAGS	=  ${COPTS} ${OPTIMIZER} ${IPATH}
#
#
OBJS=	\
	spirt.o \
	DT_Prim.o \
	DT_OctTree.o \
	DT_CamPrim.o \
	DT_LgtPrim.o \
	DT_AreaLgtPrim.o \
	DT_SpotLgtPrim.o \
	DT_PolyPrim.o \
	DT_SphPrim.o \
	DT_Procs.o \
	DT_PolyProcs.o \
	DT_SphProcs.o \
	DT_LgtProcs.o \
	DT_AreaLgtProcs.o \
	DT_SpotLgtProcs.o \
	libUtil.o \
	sgilib.o \
	libShade.o \
	${NULL}
TARGETS	=\
	spirt \
	${NULL}
LIBS	=\
	libUtil.a \
	sgilib.a \
	libShade.a \
	${NULL}

all:	${LIBS} ${TARGETS}
lib:	${LIBS}
install:
	cp ./spirt /usr/spi/thedoug/bin/.
clean:
	rm -f ${TARGETS} core a.out *.a *.o *.so


DT_Prim.o: ${SRCDIR}/DT_Prim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_Prim.C
DT_OctTree.o: ${SRCDIR}/DT_OctTree.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_OctTree.C
DT_CamPrim.o: ${SRCDIR}/DT_CamPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_CamPrim.C
DT_LgtPrim.o: ${SRCDIR}/DT_LgtPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_LgtPrim.C
DT_AreaLgtPrim.o: ${SRCDIR}/DT_AreaLgtPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_AreaLgtPrim.C
DT_SpotLgtPrim.o: ${SRCDIR}/DT_SpotLgtPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_SpotLgtPrim.C
DT_PolyPrim.o: ${SRCDIR}/DT_PolyPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_PolyPrim.C
DT_SphPrim.o: ${SRCDIR}/DT_SphPrim.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_SphPrim.C
DT_Procs.o: ${SRCDIR}/DT_Procs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_Procs.C
DT_SphProcs.o: ${SRCDIR}/DT_SphProcs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_SphProcs.C
DT_PolyProcs.o: ${SRCDIR}/DT_PolyProcs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_PolyProcs.C
DT_LgtProcs.o: ${SRCDIR}/DT_LgtProcs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_LgtProcs.C
DT_AreaLgtProcs.o: ${SRCDIR}/DT_AreaLgtProcs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_AreaLgtProcs.C
DT_SpotLgtProcs.o: ${SRCDIR}/DT_SpotLgtProcs.C
	${CC} -c ${CFLAGS} ${SRCDIR}/DT_SpotLgtProcs.C
libUtil.o: ${SRCDIR}/libUtil.C
	${CC} -c ${CFLAGS} ${SRCDIR}/libUtil.C 
sgilib.o: ${SRCDIR}/sgilib.C
	${CC} -c ${CFLAGS} ${SRCDIR}/sgilib.C 
libShade.o: ${SRCDIR}/libShade.C
	${CC} -c ${CFLAGS} ${SRCDIR}/libShade.C 
spirt.o: ${SRCDIR}/spirt.C
	${CC} -c ${CFLAGS} ${SRCDIR}/spirt.C 

libUtil.a: libUtil.o
	ar -rcs libUtil.a libUtil.o
sgilib.a: sgilib.o
	ar -rcs sgilib.a sgilib.o
libShade.a: libShade.o
	ar -rcs libShade.a libShade.o
spirt: spirt.o DT_Prim.o DT_OctTree.o DT_CamPrim.o DT_LgtPrim.o DT_AreaLgtPrim.o DT_SpotLgtPrim.o DT_SphPrim.o DT_PolyPrim.o DT_Procs.o DT_SphProcs.o DT_PolyProcs.o DT_LgtProcs.o DT_AreaLgtProcs.o DT_SpotLgtProcs.o libUtil.a sgilib.a libShade.a
	${CC} -o spirt ${CFLAGS} spirt.o DT_Prim.o DT_OctTree.o DT_CamPrim.o DT_LgtPrim.o DT_AreaLgtPrim.o DT_SpotLgtPrim.o DT_SphPrim.o DT_PolyPrim.o DT_Procs.o DT_SphProcs.o DT_PolyProcs.o DT_LgtProcs.o DT_AreaLgtProcs.o DT_SpotLgtProcs.o libUtil.a sgilib.a libShade.a -lm -lgen

