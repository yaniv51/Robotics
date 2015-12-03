#include <iostream>
#include "RobotComponent/Robot.h"
#include "RobotBehavior/ObstacleAvoidance.h"
#include "RobotComponent/RobotSettings.h"
#include "RobotManager.h"

using namespace std;


int main(int argc, char** argv)
{
	Robot myRobot("localhost", 6665);
	ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
	RobotManager manager(&myRobot, &obstacleAvoidence);
	manager.Run();
}
