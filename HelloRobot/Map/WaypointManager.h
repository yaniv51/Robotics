/*
 * WaypointManager.h
 *
 *  Created on: Feb 1, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>
#include "STC.h"


class WaypointManager {
private:
	STC& stc;
	Path finePath;
	Path coarsePath;

public:
	WaypointManager(STC& stcObject);
	void buildFinePath();
	virtual ~WaypointManager();
};

#endif /* WAYPOINTMANAGER_H_ */
