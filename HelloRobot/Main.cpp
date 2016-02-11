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
#include "Managers/configurationReader.h"

using namespace std;

int main(int argc, char** argv)
{
	double x,y;
	try
	{
		configurationReader* config = new configurationReader();
		config->Read();

		x = MathHelper::ConvertMapPixelToX(config->MapResolutionCM, MAP_ROW_SIZE*config->MapResolutionCM, config->startLocation_X);
		y = MathHelper::ConvertMapPixelToY(config->MapResolutionCM, MAP_COLUMN_SIZE*config->MapResolutionCM, config->startLocation_Y);
		cout<<"start location: "<<x<<","<<y<<endl;
		xyPosition startPos(x, y);
		MapManager mapManager(config->MapResolutionCM, config->robotSize);
		Robot myRobot("localhost", 6665, startPos, config->startLocation_Yaw);
		ObstacleAvoidance obstacleAvoidence(&myRobot, myRobot.GetLaserHelper());
		mapManager.buildGraphByMap((config->map_path).c_str(), startPos, config->startLocation_X, config->startLocation_Y);
		WaypointManager wpm(mapManager.getFullSTCPath(), config->MapResolutionCM, MAP_ROW_SIZE*config->MapResolutionCM,MAP_COLUMN_SIZE*config->MapResolutionCM,  config->robotSize);
		wpm.buildWaypointVector();
		RobotManager manager(&myRobot, &obstacleAvoidence, wpm);
		manager.Run();
	}
	catch(exception& error)
	{
		cout<<error.what()<<endl;
	}
}
