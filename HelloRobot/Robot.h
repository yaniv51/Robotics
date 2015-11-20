/*
 * Robot.h
 *
 *  Created on: Nov 20, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;

#define SAMPLES 666
#define LINEAR_SPEED 0.5
#define LEFT_ANGULAR_SPEED 0.5
#define RIGHT_ANGULAR_SPEED -0.5
#define MIN_DEST_FROM_OBSTACLE 0.5
#define MAX_RANGE 4.095


class Robot {
private:
	PlayerClient *pc;
	LaserProxy *lp;
	Position2dProxy* pp;

public:
	Robot(const char* hostName, const int hostPort);
	void StartRobot();
	void CheckObstacle();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
