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
#include <vector>

#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "ParametricPoint.h"
#include "VectorTrack.h"

using namespace std;

SDL_Surface* screen;

Uint8* keys;

/* view matricies for each player */
GLfloat p1View[16];  // player 1 perspective
GLfloat p2View[16];  // player 2 perspective

double p1_X = 50.0;
double p1_Y = 0.0;
double p1_Z = 0.1;
double p1_Face = 0.0; //angle the player should be facing, in degrees

double p2_X = 0.0;
double p2_Y = 0.0;
double p2_Z = 1.0;
double p2_XRotate = 0.0;
double p2_YRotate = 0.0;
double p2_ZRotate = 0.0;
bool p2_turnLeft = false;
bool p2_turnRight = false;

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

VectorTrack vt;
double agentSpot = 0.0;

void draw_P1Model()
{
	glPushMatrix();
	glTranslatef(p1_X, p1_Y, p1_Z);
	glRotatef(p1_Face, 0, 0, 1);
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glPopMatrix();
}

void draw_P2Model()
{
	glPushMatrix();
	glTranslatef(p2_X, p2_Y, p2_Z);
	glRotatef(-p2_ZRotate, 0, 0, 1);
	glRotatef(-p2_XRotate, 1, 0, 0);

	if (p2_turnLeft)
	{
		glRotatef(-20, 0, 1, 0);
	}
	else if (p2_turnRight)
	{
		glRotatef(20, 0, 1, 0);
	}

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor3f(1, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glColor3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor3f(1, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	
	glColor3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glColor3f(1, 0, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, -0.5);
	
	glColor3f(1, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0, 1, 1);
	glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glColor3f(1, 0, 1);
        glVertex3f(0.0, 1.0, 0.0);
 	glColor3f(0, 1, 1);
	glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glColor3f(1, 0, 1);
        glVertex3f(0.0, 1.0, 0.0);
 	glColor3f(0, 1, 1);
	glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glColor3f(1, 0, 1);
        glVertex3f(0.0, 1.0, 0.0);
 	glColor3f(0, 1, 1);
	glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glColor3f(1, 0, 1);
        glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	
	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);
	glEnd();

	glPopMatrix();
}

void draw_ParametricPoint(ParametricPoint* pr)
{
	glPushMatrix();
	glTranslatef(pr->x, pr->y, 0.0);
	glRotatef(-(pr->normalDirection), 0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);
	glVertex3f(0.0, 0.0, 0.1);
	glVertex3f(0.0, 5.0, 0.1);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.1);
	glEnd();
	glPopMatrix();
}

//quick function to get green grass
void draw_renderGround()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0.1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glVertex3f(100, 100, 0);
	glVertex3f(100, 0, 0);
	glEnd();
	
	glLineWidth(2.0f);

        glColor3f(0, 0.8, 0.5);
	glBegin(GL_LINES);
	for (int i = 0; i < 10; i++)
	{
		glVertex3f(i*10, 0, 0.01);
		glVertex3f(i*10, 100, 0.01);
		glVertex3f(0, i*10, 0.01);
		glVertex3f(100, i*10, 0.01);
	}
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
	
	for(std::vector<ParametricPoint>::iterator it = vt.pointList.begin(); it != vt.pointList.end(); ++it)
	{
		draw_ParametricPoint(&(*it));
	}
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
	
	for(std::vector<ParametricPoint>::iterator it = vt.pointList.begin(); it != vt.pointList.end(); ++it)
	{
		draw_ParametricPoint(&(*it));
	}
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
			
			/*if (keys[SDLK_d])
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
			}   */
			if (keys[SDLK_d])
			{
				if (agentSpot < 1)
				{
					agentSpot += 0.01;
				}
			}
			if (keys[SDLK_a])
			{
				if (agentSpot > 0)
				{
					agentSpot -= 0.01;
				}
			}
			
			vt.getSpotOnTrack(agentSpot, p1_X, p1_Y, p1_Face);
			vt.computeCameraCoordinates(agentSpot, p1_camX, p1_camY, p1_camZ, p1_camXLook, p1_camYLook, p1_camZLook);

			/*p1_camX = p1_X;
			p1_camY = p1_Y - 5;
			p1_camZ = p1_Z + 5;
	                p1_camXLook = p1_X - p1_camX;
			p1_camYLook = p1_Y - p1_camY;
			p1_camZLook = p1_Z - p1_camZ;    */

			double p2_Thrust = 0.0;

			if (keys[SDLK_z])
			{
				p2_Thrust = 0.5;
			}

			//changes the rotate value based on arrow keys, and slowly snaps back
			if (keys[SDLK_DOWN])
			{
				if (p2_XRotate <= 30)
				{
					p2_XRotate += 2.0;
				}
			}
			else if (keys[SDLK_UP])
			{
				if (p2_XRotate >= -30)
				{
					p2_XRotate -= 2.0;
				}
			}
			else
			{
				if (fabs(p2_XRotate) <= 0.5)
				{
					p2_XRotate = 0.0;
				}
				else if (p2_XRotate > 0.5)
				{
					p2_XRotate -= 1.0;
				}
				else if (p2_XRotate < -0.5)
				{
					p2_XRotate += 1.0;
				}
			}
			
			if (keys[SDLK_LEFT])
			{
				p2_ZRotate -= 2.0;
				p2_turnLeft = true;
			}
			else
			{
				p2_turnLeft = false;
			}	

			if (keys[SDLK_RIGHT])
			{
				p2_ZRotate += 2.0;
				p2_turnRight = true;
			}
			else
			{
				p2_turnRight = false;
			}

			p2_X += p2_Thrust*cos((M_PI/180.0)*(p2_ZRotate - 90));
			p2_Y += p2_Thrust*sin((M_PI/180.0)*(p2_ZRotate + 90));
			p2_Z -= p2_Thrust*sin((M_PI/180.0)*(p2_XRotate));

			p2_camX = p2_X - 3*cos((M_PI/180.0)*(p2_ZRotate - 90));
			p2_camY = p2_Y - 3*sin((M_PI/180.0)*(p2_ZRotate + 90));
			p2_camZ = p2_Z + 3*sin((M_PI/180.0)*(p2_XRotate)) + 2;
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

	vt.pushPoint(10, 10, 0);
	vt.pushPoint(20, 10, 180);
	vt.pushPoint(30, 10, 270);
	vt.pushPoint(40, 10, 45);
	vt.pushPoint(50, 10, 270);
	vt.pushPoint(60, 10, 135);

	loop();

	deinit();

	return 0;
}

