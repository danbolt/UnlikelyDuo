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

double p1_X = 0.0;
double p1_Y = 0.0;
double p1_Z = 0.1;

double p2_X = 0.0;
double p2_Y = 0.0;
double p2_Z = 1.0;

double p1_camX = 0.0;
double p1_camY = 0.0;
double p1_camZ = 0.0;
double p1_camXLook = 0.0;
double p1_camYLook = 0.0;
double p1_camZLook = 0.0;

double p2_camX = 0.0;
double p2_camY = -2.5;
double p2_camZ = 5.0;
double p2_camXLook = 0.0;
double p2_camYLook = 0.0;
double p2_camZLook = 0.0;

void draw_P1Model()
{
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(p1_X, p1_Y, p1_Z);
	glVertex3f(p1_X, p1_Y + 1, p1_Z);
	glVertex3f(p1_X + 1, p1_Y + 1, p1_Z);
	glVertex3f(p1_X + 1, p1_Y, p1_Z);
	glEnd();
}

void draw_P2Model()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(p2_X, p2_Y, p2_Z);
	glVertex3f(p2_X, p2_Y + 1, p2_Z);
	glVertex3f(p2_X + 1, p2_Y + 1, p2_Z);
	glVertex3f(p2_X + 1, p2_Y, p2_Z);
	glColor3f(1, 0, 0);
	glVertex3f(p2_X, p2_Y, p2_Z);
	glColor3f(1, 0, 1);
	glVertex3f(p2_X, p2_Y, p2_Z + 1);
	glVertex3f(p2_X + 1, p2_Y, p2_Z + 1);
	glColor3f(1, 0, 0);
	glVertex3f(p2_X + 1, p2_Y, p2_Z);
	glColor3f(1, 0, 1);
	glVertex3f(p2_X, p2_Y + 1, p2_Z);
	glColor3f(1, 0, 1);
	glVertex3f(p2_X, p2_Y + 1, p2_Z + 1);
	glVertex3f(p2_X + 1, p2_Y + 1, p2_Z + 1);
	glColor3f(1, 0, 0);
	glVertex3f(p2_X + 1, p2_Y + 1, p2_Z);
	glEnd();
}

//quick function to get green grass
void draw_renderGround()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(10, 10, 0);
	glVertex3f(10, 0, 0);
	glEnd();
	
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(0, 0.8, 0.5);
	glVertex3f(5, 0, 0.01);
	glVertex3f(5, 10, 0.01);
	glVertex3f(0, 5, 0.01);
	glVertex3f(10, 5, 0.01);
	glEnd();
}

void renderP1()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(90, 1.3, 1, 75);    //uses GLU; may want to re-implement with glFrustrum later
	glViewport(0, 240, 320, 240);

	//camera placement
	gluLookAt(p1_camX, p1_camY, p1_camZ, p1_camX + p1_camXLook, p1_camY + p1_camYLook, p1_camZ + p1_camZLook, 0, 0, 1);

	draw_renderGround();

	draw_P1Model();

	draw_P2Model();
}

void renderP2()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(90, 1.3, 1, 75);    //uses GLU; may want to re-implement with glFrustrum later
	glViewport(0, 0, 320, 240);

	//camera placement
	gluLookAt(p2_camX, p2_camY, p2_camZ, p2_camXLook, p2_camYLook, p2_camZLook, 0, 0, 1);

	draw_renderGround();

	draw_P1Model();

	draw_P2Model();
}

// this is the primary rendering function. from here the two screen-drawing functions should be called
void draw()
{
	glMatrixMode(GL_MODELVIEW);
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
		
		//update block
		{
			keys = SDL_GetKeyState(NULL);
			
			if (keys[SDLK_d])
			{
				p1_X += 0.1;
			}
			if (keys[SDLK_a])
			{
				p1_X -= 0.1;
			}
			if (keys[SDLK_w])
			{
				p1_Y += 0.1;
			}
			if (keys[SDLK_s])
			{
				p1_Y -= 0.1;
			}
	
			p1_camX = p1_X;
			p1_camY = p1_Y - 5;
			p1_camZ = p1_Z + 5;
	                p1_camXLook = p1_X - p1_camX;
			p1_camYLook = p1_Y - p1_camY;
			p1_camZLook = p1_Z - p1_camZ;      \
			
			if (keys[SDLK_LEFT])
			{
				p2_X -= 0.1;
			}
			if (keys[SDLK_RIGHT])
			{
				p2_X += 0.1;
			}
			if (keys[SDLK_UP])
			{
				p2_Y += 0.1;
			}
			if (keys[SDLK_DOWN])
			{
				p2_Y -= 0.1;
			}
			
			p2_camX = p2_X;
			p2_camY = p2_Y - 3;
			p2_camZ = p2_Z + 2;
	                p2_camXLook = p2_X;
			p2_camYLook = p2_Y;
			p2_camZLook = p2_Z;
		}

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

