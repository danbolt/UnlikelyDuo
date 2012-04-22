#include <cstdlib>
#include <cstdio>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "Entity.h"

const char* Entity::classname()
{
	return "Entity";
}

void Entity::update(Uint32 currTime)
{
	entityUpdate(currTime);
}

GLfloat Entity::getX()
{
	return x;
}

GLfloat Entity::getY()
{
	return y;
}

GLfloat Entity::getZ()
{
	return z;
}

GLfloat Entity::getWidth()
{
	return width;
}

GLfloat Entity::getHeight()
{
	return height;
}

GLfloat Entity::getDepth()
{
	return depth;
}

void Entity::drawHitBox()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0); glVertex3f(width, 0, 0); glVertex3f(width, height, 0); glVertex3f(0, height, 0); glVertex3f(0, 0, 0);
	glVertex3f(width, height, depth); glVertex3f(width, 0, depth); glVertex3f(0, 0, depth); glVertex3f(0, height, depth); glVertex3f(width, height, depth);
	glEnd();
	glPopMatrix();
}

