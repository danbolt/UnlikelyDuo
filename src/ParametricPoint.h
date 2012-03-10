#ifndef PARAPOINT_H
#define PARAPOINT_H

class ParametricPoint
{
	public:
	ParametricPoint(double newX, double newY, double newNormalDirection);
	~ParametricPoint();
	
	double x,y;
	double normalDirection; //the direction that the camera should be pointing towards, in degrees
};

#endif