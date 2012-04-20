all: main.o Objects.o
	g++ -g -Wall -o ../bin/unlikelyduo main.o Objects.o -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32

main.o:
	g++ -g -Wall -c main.cpp

Objects.o:
	g++ -g -Wall -c Objects.cpp

clean:
	rm main.o Objects.o ../bin/unlikelyduo.exe
