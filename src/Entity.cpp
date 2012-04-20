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

