/*
 * STC.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef STC_H_
#define STC_H_

#include <vector>
#include "Node.h"
#include "Map.h"

using namespace std;

typedef pair<int, int> Position;

class STC {
private:
	Map &map;
	Position initialRobotPos;
	vector<vector<Node *> > graph;

	void buildGraph();
	void DFS(Node *node);


public:
	STC(Map &map, Position initialRobotPos);
	void buildSpanningTree();
	void drawSpanningTree();
	virtual ~STC();
};

#endif /* STC_H_ */
