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
#include "TestEntity.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Surface* screen;

TestEntity* en1;
TestEntity* en2;

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
	glEnable(GL_LIGHTING);
	
	// push this into its own cpp file later
	glEnable(GL_LIGHT0);
	GLfloat position[] = { 4.0f, 0.0f, 0.0f, 1.0f };
	GLfloat lightDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	
	// right now it's helpful if ambient + diffuse is the same for everything
	// we might want to make this class-specific later if it doesn't look good,
	// although this is meant to look like a playstation 1 game, keep in mind
	GLfloat ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

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
	
	gluLookAt(5, 15, 10, 0, 0, 0, 0, 0, 1);


	en1->draw();
	en2->draw();
	
	if (en2->hitTest(en1))
	{
		en2->setZ(10);
	}

	/*GLUquadricObj* someQuadric = gluNewQuadric();
	gluSphere(someQuadric , 5, 6, 6);
	gluDeleteQuadric(someQuadric);*/

	SDL_GL_SwapBuffers();
}

void mainLoop()
{
	int quit = 0;
	SDL_Event ev;
	
	en1 = new TestEntity(0, 0, -5, SDL_GetTicks(), 10, 10, 5);
	en2 = new TestEntity(-2.5f, -2.5f, 3, SDL_GetTicks(), 5, 5, 5);
	en2->zSpeed = -1;

	while (!quit)
	{
		while(SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				quit = 1;
			}
		}
		
		Uint32 ticks = SDL_GetTicks();

		en1->update(ticks);
		en2->update(ticks);
		
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
