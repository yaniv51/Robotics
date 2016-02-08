/*
 * MapManager.h
 *
 *  Created on: Feb 8, 2016
 *      Author: colman
 */

#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "../Map/Map.h"
#include "../Map/STC.h"
#include "../Helper/Defines.h"
#include "../RobotComponent/RobotSettings.h"

using namespace Defines;

class MapManager {
private:
	double _mapResolution;
	double _robotSize;
	Map map;
	STC *stc;
	Position _startPosition;

public:
	MapManager(double mapResolution, double robotSize);
	void buildGraphByMap(const char* mapPath, xyPosition startPosition);
	virtual ~MapManager();
};

#endif /* MAPMANAGER_H_ */
