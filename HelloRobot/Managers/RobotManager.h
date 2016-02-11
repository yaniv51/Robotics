/*
 * RobotManager.h
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_
#include "../RobotComponent/Robot.h"
#include "../Plans/ObstacleAvoidance.h"
#include "../Plans/Driver.h"
#include "WaypointManager.h"
#include "../Plans/WayPoint.h"

class RobotManager {
private:
	bool isRunning;
	Robot* robot;
	ObstacleAvoidance* obstacleAvoidance;
	WaypointManager& wpm;
	Driver driver;

	const double linearTolerance = 0.018;
	const double linearSpeed = 0.3;
	const double yawTolerance = 0.01;
	const double deltaTolerance = 0.02;
	const double xFactor = 0.25;
	const double yFacor = 0.125;

	xyPosition currPos;

	void moveRobot(WayPoint* wayPoint);
	void moveForward(xyPosition targetPos, double yaw, int direction, bool yawOnStart);
	void getCurrentPos();
	void moveToNextYaw(xyPosition targetPos, double yaw);
	void moveToStartPoint(WayPoint* waypoint);

public:
	void Run();
	void Stop();

	RobotManager(Robot* myRobot, ObstacleAvoidance* myObsAvoidance, WaypointManager& wayManager);
	virtual ~RobotManager();
};

#endif /* ROBOTMANAGER_H_ */
