/*
 * Driver.h
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "../RobotComponent/Robot.h"
#include "../Helper/Defines.h"
#include "WayPoint.h"
#include "../RobotComponent/RobotSettings.h"

using namespace Defines;

class Driver {
private:
	const double linearTolerance = 0.01;
	const double linearSpeed = 0.6;

	xyPosition currPos;

	Robot *robot;
	void moveForward(xyPosition targetPos, double yaw, int direction);
	void turn(double newDirection);
	void getCurrentPos();
public:
	Driver(Robot* newRobot);
	void moveRobot(WayPoint* wayPoint);
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
