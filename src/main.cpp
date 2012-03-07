/* UNLIKELY DUO
 * PROTOTYPE PRE-ALPHA MAIN FILE
 * Copyright Daniel Savage 2012
 * 
 * This is pre-alpha code, which is primarily used for concept testing.
 * Future code may be used from here, but changes may be made.
 */


#include <cstdio>
#include <cmath>
#include <cstdlib>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

SDL_Surface* screen;

Uint8* keys;

/* view matricies for each player */
GLfloat p1View[16];  // player 1 perspective
GLfloat p2View[16];  // player 2 perspective

double p1X = 0.0;
double p1Y = 0.0;
double p1Z = 0.0;
double p1XRotation = 0.0;
double p1YRotation = 0.0;
double p1ZRotation = 0.0;

double p2X = 0.0;
double p2Y = 0.0;
double p2Z = 0.0;
double p2XRotation = 0.0;
double p2YRotation = 0.0;
double p2ZRotation = 0.0;

void renderP2()
{
	glViewport(0, 240, 320, 240);

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0,0);
	glVertex2f(1,0);
	glVertex2f(1,1);
	glVertex2f(0,1);
	glEnd();
}

void renderP1()
{
	glViewport(0, 0, 320, 240);

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex2f(0,0);
	glVertex2f(1,0);
	glVertex2f(1,1);
	glVertex2f(0,1);
	glEnd();
}

// this is the primary rendering function. from here the two screen-drawing functions should be called
void draw()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	renderP1();
	renderP2();

	SDL_GL_SwapBuffers();
}

void loop()
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

		// potential update function goes here

		draw();

		SDL_Delay(20);
	}
}

// initalization function for things like SDL and OpenGL
int init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		perror("Error initalizing SDL");
		return 0;
	}

	if ((screen = SDL_SetVideoMode(320, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL)) == NULL)
	{
		perror("Error initalizing screen");
		return 0;
	}
	
	SDL_WM_SetCaption("Unlikely Duo Pre-Alpha", NULL);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	return 1;
}

// deinitalization function for things like SDL and perhaps objects
int deinit()
{
	SDL_Quit();

	return 1;
}

int main (int argc, char* argv[])
{
	init();
	
	loop();
	
	deinit();

	return 0;
}

