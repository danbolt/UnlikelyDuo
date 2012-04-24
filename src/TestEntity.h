// this is a test class I've made up to get things rolling

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "Entity.h"

class TestEntity : public Entity
{
	public:
	TestEntity(GLfloat newX, GLfloat newY, GLfloat newZ,  Uint32 currTime);
	TestEntity(GLfloat newX, GLfloat newY, GLfloat newZ,  Uint32 currTime, GLfloat newWidth, GLfloat newHeight, GLfloat newDepth);
	~TestEntity();
	
	// should return "TestEntity"
	const char* classname();
	
	void entityUpdate(Uint32 currTime);
	void draw();
	
	void setZ(GLfloat newZ);

	protected:
	//
};

#endif
