/*
 * STC.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "STC.h"

STC::STC(Map &map, Position initialRobotPos) : map(map), coarseGraph() {
	this->initialRobotPos = initialRobotPos;
}

void STC::buildGraph()
{
	int i, j;
	const Grid& coarseGrid = map.getCoarseGrid();
	const Grid& fineGrid = map.getFineGrid();

	buildGraphByGrid(coarseGrid, coarseGraph);

	i = initialRobotPos.first;
	j = initialRobotPos.second;

	if(coarseGraph.at(i).at(j))
	{
		coarseGraph.at(i).at(j)->getAllPossibleMves(coarseGraph);
		//path.push_back(coarseGraph[i][j]->getPosition());
		DFS(coarseGraph[i][j], coarseGraph);
	}
	//printGraph(coarseGraph);
	buildFineGraph(fineGrid);
	//buildSTCPath();

}

void STC::DFS(Node *node, const Node::Graph& myGraph) {
	if(!node->visited)
		path.push_back(node->getPosition());
	node->visited = true;
	for(vector<Node*>::iterator itBegin = node->neighborsInTree.begin();
			itBegin != node->neighborsInTree.end(); itBegin++)
	{
		if(!(*itBegin)->visited)
		{
			//get all possible moves for current node
			//Add tree edge between node and neighbor

			//path.push_back((*node->neighborsInTree.begin())->getPosition());
			(*itBegin)->getAllPossibleMves(myGraph);
			DFS((*itBegin), myGraph);
			//path.push_back((*node->neighborsInTree.begin())->getPosition());
		}
	}
	path.push_back(node->getPosition());
	cout<<"end ("<<node->row<<","<<node->col<<")"<<endl;
}

void STC::buildFineGraph(const Grid& fineGrid)
{
	//build new fine graph
	buildGraphByGrid(fineGrid, fineGraph);
	for(unsigned int i = 0; i<coarseGraph.size(); i++)
	{
		for(unsigned j = 0; j<coarseGraph[0].size(); j++)
		{
			fineGraph.at(i*2).at(j*2)->visited = coarseGraph.at(i).at(j)->visited;
		}
	}

	//printGraph(fineGraph);
}

//generic creation of graph by grid
void STC::buildGraphByGrid(const Grid& grid, Node::Graph& graph)
{
	unsigned i, j;
	//resize graph
	graph.resize(grid.size());
	for(i= 0; i<(int)grid.size(); i++)
		graph[i].resize(grid[i].size());

	//build start coarseGraph
	for(i = 0; i<(int)grid.size(); i++)
	{
		for(j = 0; j<(int)grid[i].size(); j++)
		{
			graph[i][j] = new Node(i, j, grid[i][j]);
		}
	}
}

void STC::printGraph(const Node::Graph& myGraph)
{
	int rows = myGraph.size();
	int cols = myGraph[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (myGraph[i][j]->isWall ? "*" : (myGraph[i][j]->visited ? "+" : " "));
		}
		cout << endl;
	}
}

void STC::buildSTCPath()
{
	Position lastPos;
	Position oldPos;
	oldPos=path[0];
	lastPos=path[1];

	cout<<"STC path:"<<endl;
	for(unsigned int i=0; i<path.size(); i++)
	{
		if(i!=0)
		{
			//check if change direction
			//if(isDifferentDirection(oldPos, lastPos, path[i]))
				//cout<<endl;
		}
		cout<<"["<<path[i].first<<","<<path[i].second<<"] ->";
		if(i!=0)
		{
			oldPos = lastPos;
			lastPos = path[i];
		}
	}
	cout<<endl;

	cout<<"STC path:"<<endl;
	for(unsigned int i=0; i<path.size(); i++)
	{
		cout<<"["<<path[i].first*2<<","<<path[i].second*2<<"] ->";
	}
	cout<<endl;

}

bool STC::isDifferentDirection(Position oldPos, Position lastPos, Position newPos)
{
	bool change = false;

	//check if direction on same row
	if(oldPos.first == lastPos.first)
	{


	}
	//otherwise, on same column
	else
	{

	}

	return change;
}

STC::~STC() {
	for(int i= 0; i<(int)coarseGraph.size(); i++)
		for(int j=0; j<(int)coarseGraph[0].size(); j++)
			delete(coarseGraph[i][j]);
	coarseGraph.clear();
	path.clear();
}
