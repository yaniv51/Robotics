#include <iostream>
#include "RobotComponent/Robot.h"
#include "RobotComponent/RobotSettings.h"
#include "Plans/ObstacleAvoidance.h"
#include "Map/Map.h"
#include "Map/STC.h"
#include "Managers/RobotManager.h"
#include "Managers/WaypointManager.h"

using namespace std;

int main(int argc, char** argv)
{
	Map map(MAP_RESOLUTION, ROBOT_SIZE);

	Position FinePos = map.convertPointToFinePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	Position CoarsePos = map.convertPointToCoarsePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	cout<<"start point: "<<"["<<CoarsePos.first<<","<<CoarsePos.second<<"]"<<endl;

	//Robot myRobot("localhost", 6665, (double)FinePos.first, (double)FinePos.second);
	//ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
	//RobotManager manager(&myRobot, &obstacleAvoidence);

	const char *filePath = "roboticLabMap.png";
	map.loadMapFromFile(filePath);

	STC stc(map, CoarsePos);
	stc.buildGraph();
	map.addPathToFile("MapWithPath.png", stc.getCoarseGraph(), stc.getGraphColumns(), stc.getGraphRows());
	//map.addFullPathToFile("MapWithPath.png", stc.getPath(), stc.getGraphColumns(), stc.getGraphRows());
	map.addFinePathToFile("MapWithPath.png", stc.getFineGtaph(), stc.getFineGraphColumns(), stc.getFineGraphRows());
	WaypointManager wpm(stc.getNodePath(), 10.0, MAP_RESOLUTION);
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
