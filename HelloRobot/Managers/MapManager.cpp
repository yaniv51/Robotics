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

void MapManager::buildGraphByMap(const char* mapPath, xyPosition startPosition, int startColumn, int startRow)
{
	map.setInflationRadius(_robotSize);
	map.loadMapFromFile(mapPath);
	Point newPoint = map.convertPointToCoarsePoint(startColumn, startRow);
	_startPosition = Position(newPoint.first, newPoint.second);

	stc = new STC(map, _startPosition);
	//build graph
	stc -> buildGraph();

	//add full path to new map file
	map.addPathToFile("MapWithPath.png", stc->getCoarseGraph(), stc->getGraphColumns(), stc->getGraphRows(), true);
	map.addPathToFile("MapWithPath.png", stc->getFineGtaph(), stc->getFineGraphColumns(), stc->getFineGraphRows(), false);
}

Path MapManager::getFullSTCPath()
{
	if(stc!=NULL)
		return stc->getPath();
	return Path();
}

MapManager::~MapManager() {
	delete stc;
}

