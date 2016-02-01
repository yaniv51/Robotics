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
		coarseGraph[i][j]->setCameFrom(coarseGraph[i][j]);
		DFS(coarseGraph[i][j], coarseGraph);
	}
	//printGraph(coarseGraph);
	buildFineGraph(fineGrid);
	path.clear();
	buildSTCPath(coarseGraph[i][j]);
	printFullPath();
}

void STC::printFullPath()
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

	/*cout<<"STC path:"<<endl;
	for(unsigned int i=0; i<path.size(); i++)
	{
		cout<<"["<<path[i].first*2<<","<<path[i].second*2<<"] ->";
	}
	cout<<endl;*/
}

void STC::DFS(Node *node, const Node::Graph& myGraph) {
	int row;
	//path.push_back(node->getPosition());
	row = node->row;
	//col = node->col;

	//moving down
	if(node->cameFrom->row < row)
	{
		DFSagainstClock(node, myGraph);
	}
	//moving up
	else if(node->cameFrom->row > row)
	{
		DFSwithClock(node, myGraph);
	}
	else //on same row
	{
		DFSwithClock(node, myGraph);
	}

	//path.push_back(node->getPosition());
}

void STC::DFSwithClock(Node *node, const Node::Graph& myGraph)
{
	int col, row;

	//mark current node as visited
	node->visited = true;
	row = node->row;
	col = node->col;

	// add new neighbor for current node
	// set node we came from
	// recursive call for DFS

	//right
	if(col+1 < (int)myGraph[0].size())
	{
		if(!(myGraph.at(row).at(col+1)->isWall) && !myGraph.at(row).at(col+1)->visited)
		{
			node->addNeighbor(myGraph.at(row).at(col+1));
			myGraph.at(row).at(col+1)->setCameFrom(node);
			DFS(myGraph.at(row).at(col+1), myGraph);
		}
	}

	//up
	if(row-1 > -1)
	{
		if(!(myGraph.at(row-1).at(col)->isWall) && !(myGraph.at(row-1).at(col)->visited))
		{
			node->addNeighbor(myGraph.at(row-1).at(col));
			myGraph.at(row-1).at(col)->setCameFrom(node);
			DFS(myGraph.at(row-1).at(col), myGraph);
		}
	}

	//left
	if(col-1 > -1)
	{
		if(!(myGraph.at(row).at(col-1)->isWall) && !(myGraph.at(row).at(col-1)->visited))
		{
			node->addNeighbor(myGraph.at(row).at(col-1));
			myGraph.at(row).at(col-1)->setCameFrom(node);
			DFS(myGraph.at(row).at(col-1), myGraph);
		}
	}

	//down
	if(row+1 < (int)myGraph.size())
	{
		if(!(myGraph.at(row+1).at(col)->isWall) && !(myGraph.at(row+1).at(col)->visited))
		{
			node->addNeighbor(myGraph.at(row+1).at(col));
			myGraph.at(row+1).at(col)->setCameFrom(node);
			DFS(myGraph.at(row+1).at(col), myGraph);
		}
	}
}

void STC::DFSagainstClock(Node *node, const Node::Graph& myGraph)
{
	int col, row;

	//mark current node as visited
	node->visited = true;
	row = node->row;
	col = node->col;

	// add new neighbor for current node
	// set node we came from
	// recursive call for DFS

	//left
	if(col-1 > -1)
	{
		if(!(myGraph.at(row).at(col-1)->isWall) && !(myGraph.at(row).at(col-1)->visited))
		{
			node->addNeighbor(myGraph.at(row).at(col-1));
			myGraph.at(row).at(col-1)->setCameFrom(node);
			DFS(myGraph.at(row).at(col-1), myGraph);
		}
	}

	//down
	if(row+1 < (int)myGraph.size())
	{
		if(!(myGraph.at(row+1).at(col)->isWall) && !(myGraph.at(row+1).at(col)->visited))
		{
			node->addNeighbor(myGraph.at(row+1).at(col));
			myGraph.at(row+1).at(col)->setCameFrom(node);
			DFS(myGraph.at(row+1).at(col), myGraph);
		}
	}

	//up
	if(row-1 > -1)
	{
		if(!(myGraph.at(row-1).at(col)->isWall) && !(myGraph.at(row-1).at(col)->visited))
		{
			node->addNeighbor(myGraph.at(row-1).at(col));
			myGraph.at(row-1).at(col)->setCameFrom(node);
			DFS(myGraph.at(row-1).at(col), myGraph);
		}
	}

	//right
	if(col+1 < (int)myGraph[0].size())
	{
		if(!(myGraph.at(row).at(col+1)->isWall) && !myGraph.at(row).at(col+1)->visited)
		{
			node->addNeighbor(myGraph.at(row).at(col+1));
			myGraph.at(row).at(col+1)->setCameFrom(node);
			DFS(myGraph.at(row).at(col+1), myGraph);
		}
	}
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
	for(i= 0; i<grid.size(); i++)
		graph[i].resize(grid[i].size());

	//build start coarseGraph
	for(i = 0; i<grid.size(); i++)
	{
		for(j = 0; j<grid[i].size(); j++)
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

void STC::buildSTCPath(Node* currentPos)
{

	for(vector<Node*>::iterator itBegin = currentPos->neighborsInTree.begin();
			itBegin != currentPos->neighborsInTree.end(); itBegin++)
	{
		//cout<<"["<<currentPos->row<<","<<currentPos->col<<"]->";
		path.push_back(currentPos->getPosition());
		buildSTCPath((*itBegin));
	}
	path.push_back(currentPos->getPosition());
}

STC::~STC() {
	for(int i= 0; i<(int)coarseGraph.size(); i++)
		for(int j=0; j<(int)coarseGraph[0].size(); j++)
			delete(coarseGraph[i][j]);
	coarseGraph.clear();
	path.clear();
}
