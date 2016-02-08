/*
 * Driver.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#include "Driver.h"

Driver::Driver(Robot *newRobot){
	robot = newRobot;
}

void Driver::moveForward(xyPosition targetPos, double yaw, int direction) {
	//getCurrentPos();

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
}

void Driver::moveRobot(WayPoint* wayPoint) {
	double x,y;

	//way point is with row, column pixel -> need to change to x,y
	x = MathHelper::ConvertMapPixelToX(MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION, wayPoint->x_Coordinate);
	y = MathHelper::ConvertMapPixelToY(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, wayPoint->y_Coordinate);

	xyPosition targetPos(x, y);
	moveForward(targetPos, wayPoint->yaw, wayPoint->direction);
}

void Driver::getCurrentPos() {
	robot->Refresh();
	currPos.first = robot->GetX();
	currPos.second = robot->GetY();

	cout << "curr pos: " << currPos.first << "," << currPos.second << endl;
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

