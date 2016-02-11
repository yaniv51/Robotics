/*
 * WaypointManager.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

WaypointManager::WaypointManager(Path path, double robotMapResolution, double robotRowMapSize, double robotColumnMapSize, float robotSize)
{
	_stc_path = path;
	_mapResolution = robotMapResolution;
	_robotRowMapSize = robotRowMapSize;
	_robotColumnMapSize = robotColumnMapSize;
	currentWayPoint = 0;
	robotSizeInCells = robotSize / (float)robotMapResolution;
}


void WaypointManager::buildWaypointVector()
{
	int nextDirection;

	cout<<"STC size: "<< _stc_path.size()<<endl;
	for (unsigned int i = 0; i < _stc_path.size()-1; i++)
	{
		nextDirection = getNextDirection(_stc_path.at(i), _stc_path.at(i+1));
		addWayPoint(_stc_path.at(i), nextDirection);
	}
	cout<<"way points size: "<<wayPoints.size()<<endl;
}

Point WaypointManager::convertFinePointToMapPixel(int row, int col)
{
	Point newPoint(row*robotSizeInCells, col*robotSizeInCells);
	return newPoint;
}

void WaypointManager::addWayPoint(Position nextPos, int direction)
{
	double x, y, yaw;

	y = nextPos.first*robotSizeInCells;
	x = nextPos.second*robotSizeInCells;

	//convert pixel point to map point
	x = MathHelper::ConvertMapPixelToX(_mapResolution, MAP_ROW_SIZE*_mapResolution, x);
	y = MathHelper::ConvertMapPixelToY(_mapResolution, MAP_COLUMN_SIZE*_mapResolution, y);

	switch(direction)
	{
	case MOVING_UP:
		yaw = MathHelper::ConvertDegreeToRadian(90);
		break;
	case MOVING_DOWN:
		yaw = MathHelper::ConvertDegreeToRadian(-90);
		break;
	case MOVING_RIGHT:
		yaw = MathHelper::ConvertDegreeToRadian(0);
		break;
	case MOVING_LEFT:
		yaw = MathHelper::ConvertDegreeToRadian(180);
		break;
	}

	//if last yaw is equal to next yaw - can ignre the way point
	if(wayPoints.size() > 0 && wayPoints[wayPoints.size()-1]->yaw == yaw)
		return;

	//fix points
	if(x < 0 && x > -0.5)
		x += xFactor;
	if(x>2.7 && x<2.8)
	{
		if(( (float)y-yFacor> 0.1 && (float)y-yFacor<0.2) ||( (float)y-yFacor>-1.1 && (float)y-yFacor<-1.05))
			x += xFactor;
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
	WayPoint* nextWayPoint = wayPoints.at(currentWayPoint);
	currentWayPoint = currentWayPoint+1;
	return nextWayPoint;
}

float WaypointManager::getCompletedPercent()
{
	return ((float)(currentWayPoint-1)/(float)wayPoints.size())*100;
}

bool WaypointManager::haveMoreWayPoints()
{
	if(currentWayPoint < (int)wayPoints.size())
		return true;
	return false;
}



WaypointManager::~WaypointManager() {
	for(unsigned int i = 0; i< wayPoints.size(); i++)
		delete (wayPoints[i]);
	wayPoints.clear();
}

