#include <iostream>
#include "RobotComponent/Robot.h"
#include "RobotComponent/RobotSettings.h"
#include "Plans/ObstacleAvoidance.h"
#include "Map/Map.h"
#include "Map/STC.h"
#include "Managers/RobotManager.h"
#include "Managers/WaypointManager.h"
#include "Helper/MathHelper.h"

using namespace std;

int main(int argc, char** argv)
{
	Map map(MAP_RESOLUTION, ROBOT_SIZE);
	//pose [2.175 -2.875 45]
	int startX, startY;
	//double x=mapToWorldX((550.0/13.75)*(13.75/2+2.17));
	//double y=mapToWorldY((380.0/9.5)*(9.5/2+2.88));
	// convert robot x,y to map pixels: ((380.0/9.5)*(9.5/2+2.88)); V (550.0/13.75)*(13.75/2+2.17)); V
	double x = MathHelper::ConvertRobotLocationToMapPixel(550, 13.75, 2.17);
	double y = MathHelper::ConvertRobotLocationToMapPixel(380, 9.5, 2.88);
	cout<<"start location: "<<x<<","<<y<<endl;
	Position FinePos = map.convertPointToFinePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	Position CoarsePos = map.convertPointToCoarsePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	cout<<"start point: "<<"["<<CoarsePos.first<<","<<CoarsePos.second<<"]"<<endl;

	/*Robot myRobot("localhost", 6665, (double)FinePos.first, (double)FinePos.second);
	ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
	RobotManager manager(&myRobot, &obstacleAvoidence);*/

	const char *filePath = "roboticLabMap.png";
	map.loadMapFromFile(filePath);

	/*STC stc(map, CoarsePos);
	stc.buildGraph();
	map.addPathToFile("MapWithPath.png", stc.getCoarseGraph(), stc.getGraphColumns(), stc.getGraphRows(), true);
	map.addPathToFile("MapWithPath.png", stc.getFineGtaph(), stc.getFineGraphColumns(), stc.getFineGraphRows(), false);*/

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
