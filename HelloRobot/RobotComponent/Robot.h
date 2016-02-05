/*
 * Robot.h
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "RobotSettings.h"
#include "Laser.h"
#include <math.h>
#include <unistd.h>

using namespace std;
using namespace PlayerCc;


class Robot {
private:
	PlayerClient* pc;
	Laser *laserHelper;
	LaserProxy *lp;
	Position2dProxy *pp;
	SonarProxy *sp;

public:
	//Robot(PlayerClient* player, Position2dProxy* posProxy, Laser* laserProxy);
	Robot(const char* hostName, const int port, int startPosX, int startPosY);
	double GetLaserProxyDistance(int index);
	double GetX();
	double GetY();
	double GetYaw();
	void SetSpeed(double forward, double angular);
	void Refresh();
	bool canRotate();
	bool canMoveForward(float distance = MIN_DEST_FROM_OBSTACLE);
	Laser* GetLaserHelper() {return laserHelper;}
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
