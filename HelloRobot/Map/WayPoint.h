/*
 * WayPoint.h
 *
 *  Created on: Feb 5, 2016
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "limits.h"

class WayPoint {
public:

	double x_Coordinate;
	double y_Coordinate;
	double yaw;

	WayPoint(double x, double y, double yaw_angle);
	WayPoint();

	bool operator<(const WayPoint& wp) const
	{
		return (y_Coordinate*INT_MAX + x_Coordinate + yaw > wp.y_Coordinate*INT_MAX + wp.x_Coordinate + yaw);
	}

	virtual ~WayPoint();
};

#endif /* WAYPOINT_H_ */
