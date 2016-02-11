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

	nextWayPoint = wpm.getNextWayPoint();
	cout<<"next waypoint: "<<nextWayPoint->x_Coordinate<<","<<nextWayPoint->y_Coordinate<<","<<nextWayPoint->yaw<<endl;
	moveToStartPoint(nextWayPoint);
	while(wpm.haveMoreWayPoints())
	{
		robot->Refresh();
		nextWayPoint = wpm.getNextWayPoint();
		moveRobot(nextWayPoint);
	}
}

void RobotManager::moveToNextYaw(xyPosition targetPos, double yaw)
{
	double speed;
	//abort robot to move if Yaw is same
	double yaw2 = robot->GetYaw();
	if(abs(robot->GetYaw() - yaw) < yawTolerance)
		return;

	yaw2 = MathHelper::ConvertRadianToDegree(yaw2);

	//set right/left speed
	if(yaw2 <95 && yaw2 > 40) //90 degree
	{
		if(yaw == MathHelper::ConvertDegreeToRadian(LOOK_LEFT) )
			speed = LEFT_ANGULAR_SPEED;
		else
			speed = RIGHT_ANGULAR_SPEED;
	}
	else if(yaw2 > -5 && yaw2 < 5) //0 degree
	{
		if(yaw == MathHelper::ConvertDegreeToRadian(LOOK_UP) )
			speed = LEFT_ANGULAR_SPEED;
		else
			speed = RIGHT_ANGULAR_SPEED;
	}
	else if(yaw2>-5 && yaw2 < 180) //180 degree
	{
		if(yaw == MathHelper::ConvertDegreeToRadian(LOOK_DOWN ))
			speed = LEFT_ANGULAR_SPEED;
		else
			speed = RIGHT_ANGULAR_SPEED;
	}
	else //-90 degree
	{
		if(yaw == 0 )
			speed = LEFT_ANGULAR_SPEED;
		else
			speed = RIGHT_ANGULAR_SPEED;
	}

	robot->SetSpeed(0,speed);
	while(abs(robot->GetYaw() - yaw) > yawTolerance*4)
		robot->Refresh();
	//slow down before reaching angle target
	robot->SetSpeed(0,speed*0.5);
	while(abs(robot->GetYaw() - yaw) < yawTolerance)
		robot->Refresh();
	robot->SetSpeed(0,0);
}

void RobotManager::moveToStartPoint(WayPoint* waypoint)
{
	double x, y, deltaX, deltaY, yaw, x1, y1;

	x = robot->GetX();
	y = robot->GetY();

	deltaX = waypoint->x_Coordinate - x;
	deltaY = waypoint->y_Coordinate - y;

	x1 = waypoint->x_Coordinate;
	y1 = waypoint->y_Coordinate;


	if(deltaX > 0)
		yaw = 0;
	else if(deltaX < 0)
		yaw = MathHelper::ConvertDegreeToRadian(180);

	xyPosition newPos(x1, y);
	cout<<"start waypoint 1: "<<x1<<","<<y<<endl;
	moveForward(newPos, yaw, 0, true);
	robot->SetSpeed(0,0);

	if(deltaY > 0 )
		yaw = MathHelper::ConvertDegreeToRadian(90);
	else
		yaw = MathHelper::ConvertDegreeToRadian(-90);

	xyPosition newPos1(x1, y1);
	cout<<"start waypoint 2: "<<x1<<","<<y1<<endl;
	moveForward(newPos1, yaw, 0, true);
	robot->SetSpeed(0,0);
}

void RobotManager::moveForward(xyPosition targetPos, double yaw, int direction, bool yawOnStart) {
	getCurrentPos();

	// change YAW for to next point
	if(yawOnStart)
		moveToNextYaw(targetPos, yaw);

	robot->SetSpeed(linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > 10 * linearTolerance ||
			abs(currPos.second - targetPos.second) > 10 * linearTolerance) {
		getCurrentPos();
	}

	// slow down before reaching the target
	robot->SetSpeed(0.05 * linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > linearTolerance ||
		abs(currPos.second - targetPos.second) > linearTolerance)
	{		getCurrentPos();
	}

	moveToNextYaw(targetPos, yaw);
}

void RobotManager::moveRobot(WayPoint* wayPoint) {
	double x,y;
	double deltaX, deltaY, startX, startY;

	x = wayPoint->x_Coordinate;
	y = wayPoint->y_Coordinate - yFacor;

	xyPosition targetPos(x, y);
	cout<<"next waypoint: "<<x<<","<<y<<","<<MathHelper::ConvertRadianToDegree(wayPoint->yaw)<<endl;
	getCurrentPos();

	//do not move x,y if smaller than the delta
	deltaX = abs(targetPos.first - currPos.first);
	deltaY = abs(targetPos.second - currPos.second);
	if(deltaX < deltaTolerance)
		deltaX = 0;
	if(deltaY < deltaTolerance)
		deltaY = 0;

	getCurrentPos();
	startX = currPos.first;
	startY = currPos.second;

	//move to next point
	robot->SetSpeed(linearSpeed, 0);
	while (abs(startX - currPos.first) < deltaX-0.2 ||
			abs(startY - currPos.second) < deltaY-0.2) {
		getCurrentPos();
	}

	// slow down before reaching the target
	robot->SetSpeed(0.05 * linearSpeed, 0);

	moveToNextYaw(targetPos, wayPoint->yaw);
}

void RobotManager::getCurrentPos() {
	robot->Refresh();
	currPos.first = robot->GetX();
	currPos.second = robot->GetY();
}

void RobotManager::Stop()
{
	isRunning = false;
}

RobotManager::~RobotManager() {
	// TODO Auto-generated destructor stub
}

