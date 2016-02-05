/*
 * WaypointManager.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

WaypointManager::WaypointManager(vector<Node> path, double gridResolution, double mapResolution)
{
	stc_path = path;
	_gridResolution = gridResolution;
	_mapResolution = mapResolution;
	is_verticle = false;
}


// Creating way point every "num_of_cells" item on the path
void WaypointManager::build_way_point_vector(int num_of_cells)
{
	set<WayPoint>::iterator iter = wayPoints.begin();
	int counter = 0;
	// map sign = >  0 = left , 1 =  right , 2 = down, 3 = up
	int currentLocation = -1;
	int currentX, currentY, nextX, nextY;
	double m;

	for (unsigned int i = 0; i < stc_path.size()-1; i++)
	{
		currentX = stc_path[i].col;
		currentY = stc_path[i].row;
		nextX = stc_path[i+1].col;
		nextY = stc_path[i+1].row;


	}
}

double WaypointManager::calc_yaw(double m, Node node_from, Node node_to)
{
	double angle;

	if(!is_verticle)
	{
		angle = 180 * atan(m) / M_PI;
	}

	if (is_verticle)
	{
		if (node_to.row > node_from.row)
		{
			return (270);
		}
		else
		{
			return (90);
		}
	}
	else if ( m == 0)
	{
		if (node_to.col > node_from.col)
		{
			return (angle);
		}
		else
		{
			return (180 + angle);
		}
	}
	else if (m > 0)
	{
		if (node_to.row > node_from.row)
		{
			return (360 - angle);
		}
		else
		{
			return (180 - angle);
		}
	}
	else
	{
		if (node_to.row > node_from.row)
		{
			return (180 + angle);
		}
		else
		{
			return (angle);
		}
	}
}

double WaypointManager::calc_incline(Node node_from, Node node_to)
{
	is_verticle = 0;
	if(node_from.col == node_to.col)
	{
		is_verticle = 1;
		return(9999);
	}
	else
	{
		return((node_to.row - node_from.row) / (node_to.col - node_from.col));
	}
}

void WaypointManager::setNextWayPoint(WayPoint Next)
{
	currWayPoint.x_Coordinate = nextWayPoint.x_Coordinate;
	currWayPoint.y_Coordinate = nextWayPoint.y_Coordinate;
	currWayPoint.yaw = nextWayPoint.yaw;

	nextWayPoint.x_Coordinate = Next.x_Coordinate;
	nextWayPoint.y_Coordinate = Next.y_Coordinate;
	nextWayPoint.yaw = Next.yaw;
}

bool WaypointManager::isInWayPoint(double x,double y)
{
	double dx = nextWayPoint.x_Coordinate - x;
	double dy = nextWayPoint.y_Coordinate - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	cout << "Next way point x: "<< nextWayPoint.x_Coordinate << " ---> current x: " << x << endl;
	cout << "Next way point y: "<< nextWayPoint.y_Coordinate << " ---> current y: " << y << endl;
	cout << "Next way point yaw" << nextWayPoint.yaw <<  endl;
	cout << "Distance to next way point: " << (distance) << endl;
	cout << endl;

	// Checking if the robot hit the way point, considering tolerance
	if (distance*_gridResolution <= TOLERANCE)
	{
		return true;
	}
	return false;
}


WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

