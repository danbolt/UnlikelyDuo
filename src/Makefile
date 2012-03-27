all: unlikelyduo

unlikelyduo: md2.o texture.o tga.o bmp.o pcx.o VectorTrack.o ParametricPoint.o main.o
	g++ -g -Wall md2.o texture.o tga.o bmp.o pcx.o VectorTrack.o ParametricPoint.o main.o -o ../bin/unlikelyduo -lmingw32 -lSDLmain -lopengl32 -lglu32 -lSDL

main.o:
	g++ -g -Wall -c main.cpp
	
ParametricPoint.o:
	g++ -g -Wall -c ParametricPoint.cpp
	
VectorTrack.o:
	g++ -g -Wall -c VectorTrack.cpp

md2.o:
	g++ -g -Wall -c md2.cpp

texture.o:
	g++ -g -Wall -c texture.cpp

tga.o:
	g++ -g -Wall -c tga.cpp

bmp.o:
	g++ -g -Wall -c bmp.cpp

pcx.o:
	g++ -g -Wall -c pcx.cpp

clean:
	rm *.o ../bin/unlikelyduo*

clean-objects:
	rm *.o

