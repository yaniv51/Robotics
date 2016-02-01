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
	Node::Graph coarseGraph;
	Node::Graph fineGraph;
	Path path;

	void DFS(Node *node, const Node::Graph& myGraph);
	void printGraph(const Node::Graph& myGraph);
	void printDFS();
	bool isDifferentDirection(Position oldPos, Position lastPos, Position newPos);
	void buildGraphByGrid(const Grid& grid, Node::Graph& graph);

public:
	STC(Map &map, Position initialRobotPos);
	void buildGraph();
	void buildSpanningTree();
	void drawSpanningTree();
	void buildFineGraph(const Grid& fineGrid);
	void buildSTCPath();
	Path getPath() {return path;}
	Position getInitialRobotPosition() {return initialRobotPos;}
	Node::Graph& getCoarseGraph(){return coarseGraph;}
	int getGraphRows(){return coarseGraph.size();}
	int getGraphColumns(){return coarseGraph[0].size();}
	virtual ~STC();
};

#endif /* STC_H_ */
