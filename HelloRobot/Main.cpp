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

	/*double x = MathHelper::ConvertXRobotLocationToMapPixel(MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION, ROBOT_START_X);
	double y = MathHelper::ConvertYRobotLocationToMapPixel(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, ROBOT_START_Y);
	cout<<"start location: "<<x<<","<<y<<endl;
	cout<<"original: "<<START_LOCATION_COLUMN<<","<<START_LOCATION_ROW<<endl;
	x = MathHelper::ConvertMapPixelToX(MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION, x);
	y = MathHelper::ConvertMapPixelToY(MAP_RESOLUTION, MAP_COLUMN_SIZE*MAP_RESOLUTION, y);
	cout<<"start location: "<<x<<","<<y<<endl;*/

	MapManager mapManager(MAP_RESOLUTION, ROBOT_SIZE);
	Point FinePos = mapManager.getMap().convertPointToFinePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	Robot myRobot("localhost", 6665, (double)FinePos.first, (double)FinePos.second);
	//Robot myRobot("localhost", 6665, (double)0, (double)0);
	ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());

	mapManager.buildGraphByMap(filePath, startPos);

	WaypointManager wpm(mapManager.getFullSTCPath(), MAP_RESOLUTION, MAP_ROW_SIZE*MAP_RESOLUTION,MAP_COLUMN_SIZE*MAP_RESOLUTION);
	wpm.buildWaypointVector();

	RobotManager manager(&myRobot, &obstacleAvoidence, wpm);
	manager.Run();
}
