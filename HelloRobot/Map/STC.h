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
typedef vector<Position> Path;

class STC {
private:
	Map &map;
	Position initialRobotPos;
	Node::Graph graph;
	Path path;

	void DFS(Node *node, const Node::Graph& myGraph);
	void printGraph(const Node::Graph& myGraph);
	void printDFS();


public:
	STC(Map &map, Position initialRobotPos);
	void buildGraph();
	void buildSpanningTree();
	void drawSpanningTree();
	void buildSTCPath();
	Path getPath() {return path;}
	Position getInitialRobotPosition() {return initialRobotPos;}
	virtual ~STC();
};

#endif /* STC_H_ */
