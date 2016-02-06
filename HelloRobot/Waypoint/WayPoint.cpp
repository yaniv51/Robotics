/*
 * WayPoint.cpp
 *
 *  Created on: Feb 5, 2016
 *      Author: colman
 */

#include "WayPoint.h"

WayPoint::WayPoint(double x, double y, double yaw_angle) {
	x_Coordinate = x;
	y_Coordinate = y;
	yaw = yaw_angle;
}

WayPoint::WayPoint()
{

}

WayPoint::~WayPoint() {
	// TODO Auto-generated destructor stub
}

