/*
 * WaypointManager.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

WaypointManager::WaypointManager(Path path, double robotMapResolution, double robotRowMapSize, double robotColumnMapSize)
{
	_stc_path = path;
	_mapResolution = robotMapResolution;
	_robotRowMapSize = robotRowMapSize;
	_robotColumnMapSize = robotColumnMapSize;
	currentWayPoint = 0;
	robotSizeInCells = (float)ROBOT_SIZE / (float)robotMapResolution;
}


void WaypointManager::buildWaypointVector()
{
	int nextDirection, lastDirection;

	for (unsigned int i = 0; i < _stc_path.size()-1; i++)
	{
		int size = _stc_path.size();
		nextDirection = getNextDirection(_stc_path.at(i), _stc_path.at(i+1));
		addWayPoint(_stc_path.at(i), nextDirection);
	}
}

Point WaypointManager::convertFinePointToMapPixel(int row, int col)
{
	Point newPoint(row*robotSizeInCells, col*robotSizeInCells);
	return newPoint;
}

void WaypointManager::addWayPoint(Position nextPos, int direction)
{
	double x, y, yaw;

	//convert fine point to map point
	//x = MathHelper::ConvertXRobotLocationToMapPixel(_mapResolution, _robotRowMapSize, nextPos.first);
	//y = MathHelper::ConvertYRobotLocationToMapPixel(_mapResolution, _robotColumnMapSize, nextPos.second);

	y = nextPos.first*robotSizeInCells;
	x = nextPos.second*robotSizeInCells;


	switch(direction)
	{
	case MOVING_UP:
		yaw = MathHelper::ConvertDegreeToRadian(90);
		break;
	case MOVING_DOWN:
		yaw = MathHelper::ConvertDegreeToRadian(270);
		break;
	case MOVING_RIGHT:
		yaw = MathHelper::ConvertDegreeToRadian(0);
		break;
	case MOVING_LEFT:
		yaw = MathHelper::ConvertDegreeToRadian(180);
		break;
	}

	//cout<<"next way point"<<x<<","<<y<<","<<yaw<<endl;
	wayPoints.push_back(new WayPoint(x, y, yaw, direction));
}

int WaypointManager::getNextDirection(Position currentPos, Position nextPosition)
{
	if(currentPos.first > nextPosition.first)
	{
		//going up
		return MOVING_UP;
	}
	else if(currentPos.first < nextPosition.first)
	{
		//going down
		return MOVING_DOWN;
	}
	else
	{
		if(currentPos.second > nextPosition.second)
		{
			//going left
			return MOVING_LEFT;
		}
		else if(currentPos.second <= nextPosition.second)
		{
			//going right
			return MOVING_RIGHT;
		}
	}
	return 0;
}

WayPoint* WaypointManager::getNextWayPoint()
{
	WayPoint* nextWayPoint = wayPoints.at(currentWayPoint+1);
	currentWayPoint = currentWayPoint+1;
	return nextWayPoint;
}

bool WaypointManager::haveMoreWayPoints()
{
	if(currentWayPoint < wayPoints.size())
		return true;
	return false;
}

/*double WaypointManager::calc_yaw(double m, Node node_from, Node node_to)
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
}*/

/*bool WaypointManager::isInWayPoint(double x,double y)
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
	if (distance*_mapResolution <= TOLERANCE)
	{
		return true;
	}
	return false;
}*/


WaypointManager::~WaypointManager() {
	for(unsigned int i = 0; i< wayPoints.size(); i++)
		delete (wayPoints[i]);
	wayPoints.clear();
}

