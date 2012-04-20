/* the world object is the base root for all other objects
 * it includes functionality that should be standard to all
 * objects in the game world
 */
 
#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SDL/SDL.h>
#include <GL/gl.h>

class WorldObject
{
	public:
	// returns a character string of the class name
	// in this case, would return "WorldObject"
	virtual const char* classname() = 0;
	
	virtual void update(Uint32 currTime) = 0;
	virtual void draw() = 0;

	protected:
	//
};

#endif
