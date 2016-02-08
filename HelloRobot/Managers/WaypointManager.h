/*
 * WaypointManager.h
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>
#include <math.h>
#include <iostream>
#include "../Plans/WayPoint.h"
#include "../RobotComponent/RobotSettings.h"
#include "../Helper/Defines.h"
#include "../Helper/MathHelper.h"

using namespace std;
using namespace Defines;


#define TOLERANCE 10

class WaypointManager {
private:
	Path _stc_path;
	vector<WayPoint*> wayPoints;
	bool is_verticle;
	int currentWayPoint;
	double _mapResolution;
	double _robotRowMapSize, _robotColumnMapSize;
	int robotSizeInCells;

	int getNextDirection(Position currentPos, Position nextPos);
	void addWayPoint(Position nextPos, int direction);
	Point convertFinePointToMapPixel(int row, int col);

	//double calc_yaw(double m, Node node_from, Node node_to);
	//double calc_incline(Node node_from, Node node_to);


public:
	WaypointManager(Path path, double robotMapResolution, double robotRowMapSize, double robotColumnMapSize);
	void buildWaypointVector();
	WayPoint* getNextWayPoint();
	bool haveMoreWayPoints();

	//void setNextWayPoint(WayPoint Next);
	//bool isInWayPoint(double x,double y);
	virtual ~WaypointManager();
};

#endif /* WAYPOINTMANAGER_H_ */
