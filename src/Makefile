all: unlikelyduo

unlikelyduo: ParametricPoint.o main.o
	g++ -g -Wall ParametricPoint.o main.o -o ../bin/unlikelyduo -lmingw32 -lSDLmain -lopengl32 -lglu32 -lSDL

main.o:
	g++ -g -Wall -c main.cpp
	
ParametricPoint.o:
	g++ -g -Wall -c ParametricPoint.cpp

clean:
	rm *.o ../bin/unlikelyduo*

clean-objects:
	rm *.o

