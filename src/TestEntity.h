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
	~TestEntity();
	
	// should return "TestEntity"
	const char* classname();
	
	void entityUpdate(Uint32 currTime);
	void draw();
	
	bool hitTest(Entity* other);
	void getDisplacement(Entity* other, GLfloat &xDis, GLfloat &yDis, GLfloat &zDis);

	protected:
	//
};

#endif
