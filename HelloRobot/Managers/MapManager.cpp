/*
 * MapManager.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: colman
 */

#include "MapManager.h"

MapManager::MapManager(double mapResolution, double robotSize) : map(mapResolution, robotSize){
	_mapResolution = mapResolution;
	_robotSize = robotSize;
	stc = NULL;

}

void MapManager::buildGraphByMap(const char* mapPath, xyPosition startPosition)
{
	map.loadMapFromFile(mapPath);
	Point newPoint = map.convertPointToCoarsePoint(START_LOCATION_COLUMN, START_LOCATION_ROW);
	_startPosition = Position(newPoint.first, newPoint.second);

	stc = new STC(map, _startPosition);
	//build graph
	stc -> buildGraph();

	//add full path to new map file
	map.addPathToFile("MapWithPath.png", stc->getCoarseGraph(), stc->getGraphColumns(), stc->getGraphRows(), true);
	map.addPathToFile("MapWithPath.png", stc->getFineGtaph(), stc->getFineGraphColumns(), stc->getFineGraphRows(), false);
}

MapManager::~MapManager() {
	delete stc;
}

