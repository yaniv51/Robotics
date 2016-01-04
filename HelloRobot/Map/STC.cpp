/*
 * STC.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "STC.h"

STC::STC(Map &map, Position initialRobotPos) : map(map), graph() {
	this->initialRobotPos = initialRobotPos;
}

void STC::buildGraph()
{
	int i, j;
	const Grid& coarseGrid = map.getCoarseGrid();

	//resize graph
	graph.resize(coarseGrid.size());
	for(i= 0; i<(int)coarseGrid.size(); i++)
		graph[i].resize(coarseGrid[i].size());

	//build start graph
	for(i = 0; i<(int)coarseGrid.size(); i++)
	{
		for(j = 0; j<(int)coarseGrid[i].size(); j++)
		{
			graph[i][j] = new Node(i, j, coarseGrid[i][j]);
		}
	}

	i = initialRobotPos.first;
	j = initialRobotPos.second;

	printGraph(graph);

	if(graph.at(i).at(j))
	{
		graph.at(i).at(j)->getAllPossibleMves(graph);
		DFS(graph[i][j], graph);
	}
}

void STC::DFS(Node *node, const Node::Graph& myGraph) {
	node->visited = true;
	for(vector<Node*>::iterator itBegin = node->neighborsInTree.begin();
			itBegin != node->neighborsInTree.end(); itBegin++)
	{
		if(!(*itBegin)->visited)
		{
			//get all possible moves for current node
			// Add tree edge between node and neighbor
			(*itBegin)->getAllPossibleMves(myGraph);
			DFS((*itBegin), myGraph);
		}
	}
	cout<<"end ("<<node->row<<","<<node->col<<")"<<endl;
}

void STC::printGraph(const Node::Graph& myGraph)
{
	int rows = myGraph.size();
	int cols = myGraph[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (myGraph[i][j]->isWall ? "*" : " ");
		}
		cout << endl;
	}
}

STC::~STC() {
	for(int i= 0; i<(int)graph.size(); i++)
		for(int j=0; j<(int)graph[0].size(); j++)
			delete(graph[i][j]);
	graph.clear();
}
