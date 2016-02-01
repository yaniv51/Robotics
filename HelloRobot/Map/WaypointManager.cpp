/*
 * WaypointManager.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#include "WaypointManager.h"

WaypointManager::WaypointManager(STC& stcObject) : stc(stcObject),coarsePath(stc.getPath()){

}

void WaypointManager::buildFinePath()
{
	Position startPos = stc.getInitialRobotPosition();


	for(unsigned int i = 0; i< coarsePath.size(); i++)
	{

	}
}

WaypointManager::~WaypointManager() {
	// TODO Auto-generated destructor stub
}

