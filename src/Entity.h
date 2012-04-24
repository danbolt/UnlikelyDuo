/*
 * an entity is meant to represent anything that has physical
 * properties in the game world (players, bullets, etc)
 */
 
#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "WorldObject.h"

class Entity : public WorldObject
{
	public:
	// should return "Entity"
	virtual const char* classname();

	void update(Uint32 currTime);
	virtual void entityUpdate(Uint32 currTime) = 0; // entityUpdate() is called instead of update
	virtual void draw() = 0;
	
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
	GLfloat getWidth();
	GLfloat getHeight();
	GLfloat getDepth();

	// draws a pseudo wide box of dimensions in data
	void drawHitBox();

	// checks if other entity's box overlaps with this entity
	// the inverse of this method [eg: other->hitTest(this)] might not return the same
	virtual bool hitTest(Entity* other);

	// if hitTest() returns true, calling this will yield how far the overlap is in the object for realignment
	virtual void getDisplacement(Entity* other, GLfloat &xDis, GLfloat &yDis, GLfloat &zDis);
	
	GLfloat xSpeed, ySpeed, zSpeed;

	protected:
	GLfloat x, y, z;
	GLfloat width, height, depth;



	Uint32 lastUpdateTime;
};

#endif

