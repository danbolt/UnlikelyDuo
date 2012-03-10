#ifndef VECTORTRACK_H
#define VECTORTRACK_H

#include <vector>

#include "ParametricPoint.h"

using namespace std;

class VectorTrack
{
	public:
		VectorTrack();
		~VectorTrack();
		
		//pushes a point onto the end of the track
		void pushPoint(double newX, double newY, double newNormalVector);
		double getTrackLength();

	private:
		vector<ParametricPoint> pointList;

};

#endif