/*
 * RobotManager.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#include "RobotManager.h"

RobotManager::RobotManager(Robot* myRobot, ObstacleAvoidance* myObsAvoidance) {
	robot = myRobot;
	obstacleAvoidance = myObsAvoidance;
	isRunning = false;
}

void RobotManager::Run()
{
	isRunning = true;
	while(isRunning)
	{
		robot->Refresh();
		obstacleAvoidance->CheckObstacle();
	}
}

void RobotManager::Stop()
{
	isRunning = false;
}

RobotManager::~RobotManager() {
	// TODO Auto-generated destructor stub
}

