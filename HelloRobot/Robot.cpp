/*
 * Robot.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(const char* name, const int port) {

	pc = new PlayerClient(name, port);
	lp = new LaserProxy(pc);
	pp = new Position2dProxy(pc, 0);

}

void Robot::StartRobot()
{
	while(true)
	{
		pc->Read();

		CheckObstacle();

	}
}

void Robot::CheckObstacle()
{
	bool hasLeftObstacle, hasRightObstacle, hasFrontObstacle;
	double frontObstacle, leftObstacle, rightObstacle;
	//lp - return the first obstacle at choosen point, for no obstacle get max range
	//robot oriantaion - the angle(YAW) that the robot is look for
	frontObstacle = (*lp)[SAMPLES/2];
	rightObstacle = (*lp)[(int)(SAMPLES/2.5)];
	leftObstacle = (*lp)[(int)(SAMPLES/1.5)];


	hasFrontObstacle = ( frontObstacle < MIN_DEST_FROM_OBSTACLE)? true: false;
	hasRightObstacle = ( rightObstacle< MIN_DEST_FROM_OBSTACLE)? true : false;
	hasLeftObstacle = (leftObstacle < MIN_DEST_FROM_OBSTACLE)? true : false;

	if(hasFrontObstacle || hasRightObstacle  ||hasLeftObstacle )
	{
		if(hasFrontObstacle)
		{
			if(rightObstacle < leftObstacle)
				pp->SetSpeed(0, LEFT_ANGULAR_SPEED);
			else
				pp->SetSpeed(0, RIGHT_ANGULAR_SPEED);


		}
		/*else if(hasLeftObstacle )
			pp->SetSpeed(0, RIGHT_ANGULAR_SPEED);
		else if(hasRightObstacle )
			pp->SetSpeed(0, LEFT_ANGULAR_SPEED);*/

	}
	else
	{
		pp->SetSpeed(LINEAR_SPEED, 0);
	}
}

Robot::~Robot() {
	delete pc;
	delete lp;
	delete pp;
}

