#include <iostream>
#include "RobotComponent/Robot.h"
#include "RobotComponent/RobotSettings.h"
#include "Plans/ObstacleAvoidance.h"
#include "Map/Map.h"
#include "Map/STC.h"
#include "Managers/RobotManager.h"
#include "Managers/WaypointManager.h"
#include "Helper/MathHelper.h"
#include "Managers/MapManager.h"

using namespace std;

int main(int argc, char** argv)
{
	const char *filePath = "roboticLabMap.png";
	xyPosition startPos(ROBOT_START_X, ROBOT_START_Y);

	MapManager mapManager(MAP_RESOLUTION, ROBOT_SIZE);

	/*Robot myRobot("localhost", 6665, (double)FinePos.first, (double)FinePos.second);
	ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
	RobotManager manager(&myRobot, &obstacleAvoidence);*/

	double x = MathHelper::ConvertXRobotLocationToMapPixel(MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION, ROBOT_START_X);
	double y = MathHelper::ConvertYRobotLocationToMapPixel(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, ROBOT_START_Y);
	cout<<"start location: "<<x<<","<<y<<endl;
	cout<<"original: "<<START_LOCATION_COLUMN<<","<<START_LOCATION_ROW<<endl;

	mapManager.buildGraphByMap(filePath, startPos);

	//WaypointManager wpm(stc.getNodePath(), 10.0, MAP_RESOLUTION);
	//wpm.build_way_point_vector(stc.getNodePath().size());


	//manager.Run();
	/*
	Robot robot("localhost", 6665);
	Driver driver(robot);
	Path path;
	driver.moveRobot(path);

	return 0;
	 */
}
