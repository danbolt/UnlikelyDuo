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
		void pushPoint(double newX, double newY, double newNormalDirection);

		//computes the length of the track in "units"
		double getTrackLength();
		double getSpecificTrackLength(unsigned int a, unsigned int b); //between two points
		
		// MUST supply a parametric position between [0,1] and an x/y to fill
		void getSpotOnTrack(double pos, double vertical, double& x, double& y, double &rot);
		
		// MUST supply a parametric position between [0,1] and and two x/y/z's to fill
		void computeCameraCoordinates(double pos, double& camX, double& camY, double& camZ, double& lookX, double& lookY, double& lookZ);

	//private:
		vector<ParametricPoint> pointList;

};

#endif