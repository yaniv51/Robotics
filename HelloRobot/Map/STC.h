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
	vector<Node> nodePath;
	Path finePath;

	void DFS(Node *node, const Node::Graph& myGraph);
	void DFSwithClock(Node *node, const Node::Graph& myGraph);
	void DFSagainstClock(Node *node, const Node::Graph& myGraph);
	void printGraph(const Node::Graph& myGraph);
	void buildGraphByGrid(const Grid& grid, Node::Graph& graph);
	void printFullPath();
	void printFullFinePath();
	void buildSTCPath(Node* currentPos);
	void buildFinePath();
	int getNextDirection(Position currentPos, Position nextPosition);

public:
	STC(Map &map, Position initialRobotPos);
	void buildGraph();
	void buildSpanningTree();
	void buildFineGraph(const Grid& fineGrid);
	Path getPath() {return path;}
	Position getInitialRobotPosition() {return initialRobotPos;}
	Node::Graph& getCoarseGraph(){return coarseGraph;}
	Node::Graph& getFineGtaph() {return fineGraph;}
	vector<Node>& getNodePath() {return nodePath;}
	int getGraphRows(){return coarseGraph.size();}
	int getGraphColumns(){return coarseGraph[0].size();}
	int getFineGraphRows(){return fineGraph.size();}
	int getFineGraphColumns(){return fineGraph[0].size();}
	virtual ~STC();
};

#endif /* STC_H_ */
