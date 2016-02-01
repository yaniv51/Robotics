#include <iostream>
#include "RobotComponent/Robot.h"
#include "Plans/ObstacleAvoidance.h"
#include "RobotComponent/RobotSettings.h"
#include "RobotManager.h"
#include "Map/Map.h"
#include "Map/STC.h"

using namespace std;


int main(int argc, char** argv)
{
	//Robot myRobot("localhost", 6665);
	//ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
	//RobotManager manager(&myRobot, &obstacleAvoidence);
	//manager.Run();

	float mapResolution = 0.025;
	float robotSize = 0.3;
	Map map(mapResolution, robotSize);
	Position pos = map.convertPointToFinePoint(362, 305);
	cout<<"start point: "<<"["<<pos.first<<","<<pos.second<<"]"<<endl;


	const char *filePath = "roboticLabMap.png";
	map.loadMapFromFile(filePath);

	STC stc(map, pos);
	stc.buildGraph();
	map.addPathToFile("MapWithPath.png", stc.getCoarseGraph(), stc.getGraphColumns(), stc.getGraphRows());
	/*
	Robot robot("localhost", 6665);
	Driver driver(robot);
	Path path;
	driver.moveRobot(path);

	return 0;
	 */
}
