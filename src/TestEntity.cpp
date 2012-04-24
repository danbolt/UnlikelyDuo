#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <SDL/SDL.h>
#include <Gl/gl.h>

#include "Entity.h"
#include "TestEntity.h"

TestEntity::TestEntity(GLfloat newX, GLfloat newY, GLfloat newZ,  Uint32 currTime)
{
	x = newX;
	y = newY;
	z = newZ;
	
	width = 5;
	height = 5;
	depth = 5;

	xSpeed = 0;
	ySpeed = 0;
	zSpeed = 0;
	
	lastUpdateTime = currTime;
}

TestEntity::TestEntity(GLfloat newX, GLfloat newY, GLfloat newZ,  Uint32 currTime, GLfloat newWidth, GLfloat newHeight, GLfloat newDepth)
{
	x = newX;
	y = newY;
	z = newZ;
	
	width = newWidth;
	height = newHeight;
	depth = newDepth;

	xSpeed = 0;
	ySpeed = 0;
	zSpeed = 0;
	
	lastUpdateTime = currTime;
}

TestEntity::~TestEntity()
{
	//
}

const char* TestEntity::classname()
{
	return "TestEntity";
}

void TestEntity::entityUpdate(Uint32 currTime)
{
	x += xSpeed;
	y += ySpeed;
	z += zSpeed;
	
	lastUpdateTime = currTime;
}

/*
bool TestEntity::hitTest(Entity* other)
{
	return false;
}

void TestEntity::getDisplacement(Entity* other, GLfloat &xDis, GLfloat &yDis, GLfloat &zDis)
{
	return;
}       */

void TestEntity::draw()
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glBegin(GL_QUADS);

	glNormal3d(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, height, 0);
	glVertex3f(0, height, 0);
	
	glNormal3d(-1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(0, height, depth);
	glVertex3f(0, height, 0);

        glNormal3d(0,-1,0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(width, 0, depth);
	glVertex3f(width, 0, 0);

        glNormal3d(1, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 0, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, height, 0);

        glNormal3d(0, 0, 1);
	glVertex3f(0, 0, depth);
	glVertex3f(width, 0, depth);
	glVertex3f(width, height, depth);
	glVertex3f(0, height, depth);

        glNormal3d(0, 1, 0);
	glVertex3f(0, height, 0);
	glVertex3f(0, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, height, 0);
	
	glEnd();
	
	glPopMatrix();
}

void TestEntity::setZ(GLfloat newZ)
{
	z = newZ;
}	

