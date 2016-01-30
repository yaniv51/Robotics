/*
 * ObstacleAvoidance.h
 *
 *  Created on: Dec 1, 2015
 *      Author: colman
 */

#ifndef OBSTACLEAVOIDANCE_H_
#define OBSTACLEAVOIDANCE_H_
#include "../RobotComponent/Robot.h"
#include "../Helper/MathHelper.h"
#include "../RobotComponent/RobotSettings.h"

class ObstacleAvoidance {
private:
	Robot* robot;
	Laser *laserHelper;
public:
	ObstacleAvoidance(Robot* myRobot, Laser* myLaser);
	void CheckObstacle();
	void GetObstacleLocationBaseOnCurrentLocation(double xRob, double yRob,double robotYaw, double sensorAngle,double distance );
	virtual ~ObstacleAvoidance();
};

#endif /* OBSTACLEAVOIDANCE_H_ */
