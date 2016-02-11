/*
 * Robot.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(const char* hostName, const int port, xyPosition startPos, double startYaw)
{
	pc = new PlayerClient(hostName, port);
	pp = new Position2dProxy(pc,0);
	lp = new LaserProxy(pc);
	sp = new SonarProxy(pc);
	laserHelper = new Laser(lp);

	//convert degree yaw to radian
	startYaw = MathHelper::ConvertDegreeToRadian(startYaw);

	pp->SetMotorEnable(true); //for real robot - must use this command for start moving
	pp->SetOdometry(startPos.first,startPos.second,startYaw);

	//for remove old values
		for(int i = 0; i < 15; i++)
			pc->Read();
}

double Robot::GetX()
{
	return pp->GetXPos();
}

double Robot::GetY()
{
	return pp->GetYPos();
}

double Robot::GetYaw()
{
	return pp->GetYaw();
}

double Robot::GetLaserProxyDistance(int index)
{
	return (*lp)[index];
}

void Robot::SetSpeed(double forward, double angular)
{
	pp->SetSpeed(forward, angular);
}

void Robot::Refresh()
{
	pc -> Read();
}

bool Robot::canMoveForward(float distance)
{
	return laserHelper->CanMoveForward(distance);
}

bool Robot::canRotate()
{
	return laserHelper->canRotate();
}

Robot::~Robot()
{
	delete sp;
	delete laserHelper;
	delete lp;
	delete pp;
	delete pc;
}
