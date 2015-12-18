/*
 * STC.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "STC.h"

STC::STC(Map &map, Position initialRobotPos) : map(map), initialRobotPos(initialRobotPos) {
	// TODO Auto-generated constructor stub

}

STC::~STC() {
	// TODO Auto-generated destructor stub
}

void STC::DFS(Node *node) {
	// 1. Go over all the neighbors of the node in the graph
	// 2. For each neighbor, if not visited:
	// 	  2a. Add tree edge between node and neighbor
	//    2b. Recursively call DFS with neighbor
}
