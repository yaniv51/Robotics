/*
 * WaypointManager.h
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>
#include <set>
#include <math.h>
#include "../Map/WayPoint.h"
#include "../RobotComponent/RobotSettings.h"
#include "../Map/STC.h"

using namespace std;

#define TOLERANCE 10

class WaypointManager {
public:
	set<WayPoint> wayPoints;
	WayPoint currWayPoint;

	WaypointManager(vector<Node> path, double gridResolution, double mapResolution);
	void build_way_point_vector(int num_of_cells);
	void setNextWayPoint(WayPoint Next);
	bool isInWayPoint(double x,double y);
	virtual ~WaypointManager();

private:
	vector<Node> stc_path;
	bool is_verticle;
	WayPoint nextWayPoint;
	double _gridResolution;
	double _mapResolution;

	double calc_yaw(double m, Node node_from, Node node_to);
	double calc_incline(Node node_from, Node node_to);

};

#endif /* WAYPOINTMANAGER_H_ */
