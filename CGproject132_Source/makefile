INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

	
dna2: dna2.cpp
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) dna2.cpp $(LIBRARIES)  


