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

using namespace Defines;

class Driver {
private:
	const double linearTolerance = 0.01;
	const double linearSpeed = 0.6;

	xyPosition currPos;

	Robot &robot;
	void moveForward(xyPosition targetPos);
	void turn(double newDirection);
	void getCurrentPos();
public:
	Driver(Robot &robot);
	void moveRobot(Path path);
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
