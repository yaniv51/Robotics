/*
 * WayPoint.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: colman
 */

#include "WayPoint.h"

WayPoint::WayPoint(double x, double y, double yaw_angle, int nextDirection) {
	x_Coordinate = x;
	y_Coordinate = y;
	yaw = yaw_angle;
	direction = nextDirection;
}

WayPoint::WayPoint()
{
	x_Coordinate = 0;
	y_Coordinate = 0;
	yaw = 0;
	direction = 0;
}

WayPoint::~WayPoint() {
	// TODO Auto-generated destructor stub
}

