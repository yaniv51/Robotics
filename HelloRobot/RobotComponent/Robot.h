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
#include "../Helper/MathHelper.h"
#include "Laser.h"
#include "../Helper/Defines.h"
#include <math.h>
#include <unistd.h>

using namespace std;
using namespace Defines;
using namespace PlayerCc;


class Robot {
private:
	PlayerClient* pc;
	Laser *laserHelper;
	LaserProxy *lp;
	Position2dProxy *pp;
	SonarProxy *sp;

public:
	Robot(const char* hostName, const int port, xyPosition startPos, double startYaw);
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
