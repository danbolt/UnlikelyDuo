
#include <vector>
#include <cstdio>
#include <cmath>

#include "ParametricPoint.h"
#include "VectorTrack.h"

VectorTrack::VectorTrack()
{
	//
}

VectorTrack::~VectorTrack()
{
	pointList.clear();
}

void VectorTrack::pushPoint(double newX, double newY, double newNormalDirection)
{
	ParametricPoint pp(newX, newY, newNormalDirection);
	pointList.push_back(pp);
}

double VectorTrack::getTrackLength()
{
	double sum = 0.0;

	for(std::vector<ParametricPoint>::iterator it = pointList.begin(); it != pointList.end(); ++it)
	{
		if (it + 1 != pointList.end())
		{
			sum += sqrt(pow((*(it + 1)).x - (*(it)).x, 2) + pow((*(it + 1)).y - (*(it)).y, 2));
		}
	}
	
	return sum;
}

double VectorTrack::getSpecificTrackLength(unsigned int a, unsigned int b)
{
	//don't go overboard
	if (b > pointList.size())
	{
		b = pointList.size();
	}

	double sum = 0.0;

	for(std::vector<ParametricPoint>::iterator it = pointList.begin() + a; it != pointList.begin() + b + 1; ++it)
	{
		if (it + 1 != pointList.begin() + b + 1)
		{
			sum += sqrt(pow((*(it + 1)).x - (*(it)).x, 2) + pow((*(it + 1)).y - (*(it)).y, 2));
		}
	}
	
	return sum;
}

void VectorTrack::getSpotOnTrack(double pos, double& x, double& y)
{
	if (pos <= 0 || pos >= 1)
	{
		return;
	}

	unsigned int i;

	//acquire the distance actually along the track
	double soFar = pos*getTrackLength();
	
	for (i = 0; i < pointList.size(); i++)
	{
		if (soFar <= getSpecificTrackLength(0, i))
		{
			//now recompute soFar to be where between the two points on a [0,1] scale
			soFar = (soFar - getSpecificTrackLength(0, i-1))/getSpecificTrackLength(i-1, i);
			break;
		}
	}
	
	ParametricPoint a = pointList.at(i-1);
        ParametricPoint b = pointList.at(i);

	x = (1 - soFar)*(a.x) + soFar*(b.x);
	y = (1 - soFar)*(a.y) + soFar*(b.y);
}

void VectorTrack::computeCameraCoordinates(double pos, double& camX, double& camY, double& camZ, double& lookX, double& lookY, double& lookZ)
{
	if (pos <= 0 || pos >= 1)
	{
		return;
	}

	unsigned int i;

	//acquire the distance actually along the track
	double soFar = pos*getTrackLength();
	
	for (i = 0; i < pointList.size(); i++)
	{
		if (soFar <= getSpecificTrackLength(0, i))
		{
			//now recompute soFar to be where between the two points on a [0,1] scale
			soFar = (soFar - getSpecificTrackLength(0, i-1))/getSpecificTrackLength(i-1, i);
			break;
		}
	}
	
	ParametricPoint a = pointList.at(i-1);
        ParametricPoint b = pointList.at(i);

	double x = (1 - soFar)*(a.x) + soFar*(b.x);
	double y = (1 - soFar)*(a.y) + soFar*(b.y);
	
	//compute the interpolated direction between a's and b's direction
	double midAngle = (1 - soFar)*(a.normalDirection) + soFar*(b.normalDirection);
	
	camX = x + 6*sin((M_PI/180.0)*(midAngle + 180));
	camY = y + 6*cos((M_PI/180.0)*(midAngle + 180));
	camZ = 5.0;

	lookX = x - camX;
	lookY = y - camY;
	lookZ = 0.0;
}
