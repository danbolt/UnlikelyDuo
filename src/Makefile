all: unlikelyduo

unlikelyduo: main.o
	g++ -g -Wall main.o -o ../bin/unlikelyduo -lmingw32 -lSDLmain -lopengl32 -lglu32 -lSDL

main.o:
	g++ -g -Wall -c main.cpp

clean:
	rm *.o ../bin/unlikelyduo*

clean-objects:
	rm *.o

