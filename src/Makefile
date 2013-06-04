###########################################################
# Raytracer Makefile
# The bulk of the code was provided by Chandrajit Bajaj.
#

CC = g++
CFLAGS = -Wall -ggdb
INCLUDE = -I/lusr/X11/include -I/lusr/include
LIBDIR = -L/lusr/X11/lib -L/lusr/lib
# Libraries that use native graphics hardware
LIBS = -lglut -lGLU -lGL -lpthread -lm

###########################################################
# Options if compiling on Mac
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CC = g++
CFLAGS = -Wall -g -D__MAC__
INCLUDE = 
LIBDIR = -L/lusr/X11/lib
LIBS = -framework OpenGL -framework GLUT
endif

###########################################################
# Uncomment the following line if you are using Mesa
#LIBS = -lglut -lMesaGLU -lMesaGL -lm

raytrace: raytrace.cpp raytrace.h geometry.cpp geometry.h light.cpp light.h lowlevel.cpp lowlevel.h vector.cpp vector.h matrix.cpp matrix.h misc.cpp misc.h transform.cpp transform.h color.cpp color.h test.cpp test.h sceneobject.cpp sceneobject.h material.cpp material.h 
	${CC} ${CFLAGS} ${INCLUDE} -o raytrace ${LIBDIR} raytrace.cpp geometry.cpp light.cpp lowlevel.cpp vector.cpp matrix.cpp misc.cpp transform.cpp color.cpp test.cpp sceneobject.cpp material.cpp ${LIBS} 

clean:
	rm -f raytrace *.o core
