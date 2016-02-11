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
#include <cmath>
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
	int currentWayPoint;
	double _mapResolution;
	double _robotRowMapSize, _robotColumnMapSize;
	int robotSizeInCells;
	const double xFactor = 0.25;
	const double yFacor = 0.125;

	int getNextDirection(Position currentPos, Position nextPos);
	void addWayPoint(Position nextPos, int direction);
	Point convertFinePointToMapPixel(int row, int col);


public:
	WaypointManager(Path path, double robotMapResolution, double robotRowMapSize, double robotColumnMapSize, float robotSize);
	void buildWaypointVector();
	WayPoint* getNextWayPoint();
	bool haveMoreWayPoints();
	float getCompletedPercent();
	virtual ~WaypointManager();
};

#endif /* WAYPOINTMANAGER_H_ */
