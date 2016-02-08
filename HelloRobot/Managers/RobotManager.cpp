/*
 * RobotManager.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#include "RobotManager.h"

RobotManager::RobotManager(Robot* myRobot, ObstacleAvoidance* myObsAvoidance, WaypointManager& wayManager) : wpm(wayManager), driver(robot){
	robot = myRobot;
	obstacleAvoidance = myObsAvoidance;
	isRunning = false;
}

void RobotManager::Run()
{
	isRunning = true;
	WayPoint* nextWayPoint;
	while(wpm.haveMoreWayPoints())
	{
		robot->Refresh();
		nextWayPoint = wpm.getNextWayPoint();
		moveRobot(nextWayPoint);


		//driver.moveRobot(nextWayPoint);

		//obstacleAvoidance->CheckObstacle();
	}
}

void RobotManager::moveForward(xyPosition targetPos, double yaw, int direction) {
	getCurrentPos();

	// change YAW for to next point
	while (abs(robot->GetYaw() - yaw) > 10 * linearTolerance ){
		robot->SetSpeed(0, LEFT_ANGULAR_SPEED);
		getCurrentPos();
	}

	robot->SetSpeed(linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > 10 * linearTolerance ||
			abs(currPos.second - targetPos.second) > 10 * linearTolerance) {
		getCurrentPos();
	}

	// slow down before reaching the target
	robot->SetSpeed(0.1 * linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > linearTolerance ||
		abs(currPos.second - targetPos.second) > linearTolerance)
	{		getCurrentPos();
	}
	/*while (abs(currPos.first - targetPos.first) > 10 * linearTolerance ||
			abs(currPos.second - targetPos.second) > 10 * linearTolerance) {
		getCurrentPos();

	double x = robot->GetX();
	double y = 	robot->GetY();
	double yaw = robot->GetYaw();

	//Position nextWaypointPosition = nextWayPoint->getPosition();
	double cx = MathHelper::ConvertXRobotLocationToMapPixel(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, targetPos.first);
	double cy = MathHelper::ConvertYRobotLocationToMapPixel(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, targetPos.second);

	double deltaX = cx-x;
	double deltaY = cy-y;
	double s = atan2(deltaY , deltaX);

	if (yaw >=0 && s >= 0)  {
		if (yaw > s + 0.1) {
			robot->SetSpeed(0, -0.2);
		} else if (yaw < s - 0.3) {
			robot->SetSpeed(0, 0.3);
		} else {
			robot->SetSpeed(0.4, 0);
		}
	} else if (yaw < 0 && s < 0) {
		if (yaw > s + 0.3) {
			robot->SetSpeed(0, -0.2);
		} else if (yaw < s - 0.3) {
			robot->SetSpeed(0, 0.2);
		} else {
			robot->SetSpeed(0.4, 0);
		}
	} else if (yaw >=0 && s < 0) {
		if (3.14 - yaw + 3.14 - abs(s) > yaw + abs(s)) {
			robot->SetSpeed(0, -0.2);
		} else if (3.14 - yaw + 3.14 - abs(s) < yaw + abs(s)) {
			robot->SetSpeed(0, 0.2);
		} else {
			robot->SetSpeed(0.4, 0);
		}
	} else if (yaw < 0 && s >= 0) {
		if (3.14 - abs(yaw) + 3.14 - s > abs(yaw) + s) {
			robot->SetSpeed(0, 0.2);
		} else if (3.14 - abs(yaw) + 3.14 - s < abs(yaw) + s) {
			robot->SetSpeed(0, -0.2);
		} else {
			robot->SetSpeed(0.4, 0);
		}
	}
	}*/
}

void RobotManager::moveRobot(WayPoint* wayPoint) {
	double x,y;

	//way point is with row, column pixel -> need to change to x,y
	x = MathHelper::ConvertMapPixelToX(MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION, wayPoint->x_Coordinate);
	y = MathHelper::ConvertMapPixelToY(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, wayPoint->y_Coordinate);

	xyPosition targetPos(x, y);
	moveForward(targetPos, wayPoint->yaw, wayPoint->direction);
}

void RobotManager::getCurrentPos() {
	robot->Refresh();
	currPos.first = robot->GetX();
	currPos.second = robot->GetY();

	cout << "curr pos: " << currPos.first << "," << currPos.second << endl;
}

void RobotManager::Stop()
{
	isRunning = false;
}

RobotManager::~RobotManager() {
	// TODO Auto-generated destructor stub
}

