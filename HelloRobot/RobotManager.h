/*
 * RobotManager.h
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_
#include "RobotComponent/Robot.h"
#include "Plans/ObstacleAvoidance.h"

class RobotManager {
private:
	bool isRunning;
	Robot* robot;
	ObstacleAvoidance* obstacleAvoidance;

public:
	void Run();
	void Stop();

	RobotManager(Robot* myRobot, ObstacleAvoidance* myObsAvoidance);
	virtual ~RobotManager();
};

#endif /* ROBOTMANAGER_H_ */
