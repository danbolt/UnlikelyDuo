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
