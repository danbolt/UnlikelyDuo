// Unlikely Duo Alpha
// Copyright Daniel Savage 2012
// main function

// c tools
#include <cstdio>
#include <cstdlib>
#include <cmath>

// containers
#include <vector>

// libraries
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

// other source files
#include "WorldObject.h"
#include "Entity.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Surface* screen;

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		perror("Error initalizing SDL");
		return false;
	}

	if ((screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return false;
	}
	
	SDL_WM_SetCaption("Unlikely Duo Alpha", NULL);
	
	// actually prints stdout to stdout
	freopen( "CON", "w", stdout );

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void deinit()
{
	SDL_Quit();
	
	//return;
}

void dataSetup()
{
	//
}

void draw()
{
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluPerspective(90, 1.3, 1, 75);
	glViewport(0, 0, 640, 480);
	
	gluLookAt(10, 0, 10, 0, 0, 0, 0, 0, 1);
	
	GLUquadricObj* someQuadric = gluNewQuadric();
	gluSphere(someQuadric , 5, 6, 6);
	gluDeleteQuadric(someQuadric);

	SDL_GL_SwapBuffers();
}

void mainLoop()
{
	int quit = 0;
	SDL_Event ev;

	while (!quit)
	{
		while(SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		
		draw();
		
		SDL_Delay(20);
	}
}

int main (int argc, char* argv[])
{
	if (!init())
	{
		fprintf(stderr, "Error initalizing\n");
		return 1;
	}
	
	dataSetup();
	
	mainLoop();
	
	deinit();
	
	return 0;
}
