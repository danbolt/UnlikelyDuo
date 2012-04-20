/*
 * an entity is meant to represent anything that has physical
 * properties in the game world (players, bullets, etc)
 */
 
 #include <SDL/SDL.h>
 #include <GL/gl.h>
 
 #include "WorldObject.h"
 
 class Entity : public WorldObject
 {
	public:
	// should return "Entity"
	virtual const char* classname();
	
	virtual void update(Uint32 currTime);
	virtual void draw();
	
	// draws a wire box of the object's physical dimensions
	virtual void drawHitBox();
	
	// checks if boxes overlap
	bool hitTest(Entity* other);
	
	// if hitTest() returns true, calling this will yield how far the overlap is in the object for realignment
	void getDisplacement(Entity* other, GLfloat &xDis, GLfloat &yDis, GLfloat &zDis);

	protected:
	GLfloat x, y, z;
	GLfloat width, height, depth;
 };

