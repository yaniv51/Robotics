/*
 * ObstacleAvoidance.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#include "ObstacleAvoidance.h"

ObstacleAvoidance::ObstacleAvoidance(Robot* myRobot, Laser* myLaser) {
	robot = myRobot;
	laserHelper = myLaser;
}

void ObstacleAvoidance::CheckObstacle()
{
	bool hasFrontObstacle;
	double leftObstacle, rightObstacle, obstacleDistance, obstacleAngle;
	int obstacleIndex;
	bool hasFrontObstacleAfterRotate;

	hasFrontObstacle = !laserHelper->CanMoveForward();
	if(hasFrontObstacle)
	{
		//get obstacle information
		obstacleIndex = laserHelper->GetLastObstacleIndex();
		obstacleDistance = robot->GetLaserProxyDistance(obstacleIndex);
		//obstacleAngle = laserHelper->ConverIndexToDegree(obstacleIndex);
		obstacleAngle = MathHelper::ConvertDegreeToRadian(laserHelper->ConverIndexToDegree(obstacleIndex));
		cout<<"distance: "<<obstacleDistance<<", index: "<<obstacleIndex<<", angle: "<<obstacleAngle<<endl;

		//get obstacle location by params
		GetObstacleLocationBaseOnCurrentLocation(robot->GetX(), robot->GetY(), robot->GetYaw(), obstacleAngle,obstacleDistance);

		leftObstacle = laserHelper->GetLeftRank();
		rightObstacle = laserHelper->GetRightRank();
		if(leftObstacle>=rightObstacle)
		{
			//robot.moveRight
			hasFrontObstacleAfterRotate = true;
			robot->SetSpeed(0, RIGHT_ANGULAR_SPEED);
			while(hasFrontObstacleAfterRotate)
			{
				robot->Refresh();
				hasFrontObstacleAfterRotate = !laserHelper -> CanMoveForward();
			}
			robot->SetSpeed(LINEAR_SPEED, 0);
			//cout<<"moving right"<<endl;
		}
		else
		{
			//robot.moveLeft
			hasFrontObstacleAfterRotate = true;
			robot->SetSpeed(0, LEFT_ANGULAR_SPEED);
			while(hasFrontObstacleAfterRotate)
			{
				robot->Refresh();
				hasFrontObstacleAfterRotate = !laserHelper -> CanMoveForward();
			}
			robot->SetSpeed(LINEAR_SPEED, 0);
			//cout<<"moving left"<<endl;
		}
	}
	else
	{
		//robot.moveForward
		robot->SetSpeed(LINEAR_SPEED, 0);
	}
}

void ObstacleAvoidance::GetObstacleLocationBaseOnCurrentLocation(double xRob, double yRob,double robotYaw, double sensorAngle,double distance )
{
	double x,y;

	x = xRob+distance*cos(robotYaw+sensorAngle);
	y = yRob+distance*sin(robotYaw+sensorAngle);

	cout<<"obstacle at "<<x<<","<<y<<endl;
}

ObstacleAvoidance::~ObstacleAvoidance() {
	// TODO Auto-generated destructor stub
}

