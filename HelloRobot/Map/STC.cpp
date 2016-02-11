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
		//initialize first node
		coarseGraph[i][j]->setCameFrom(coarseGraph[i][j]);
		//run DFS for start location node
		DFS(coarseGraph[i][j], coarseGraph);
	}

	buildFineGraph(fineGrid);
	//printFullPath(path);
	//printFullPath(finePath);
}

void STC::printFullPath(const Path& newPath)
{
	cout<<"STC path:"<<endl;
	for(unsigned int i=0; i<newPath.size(); i++)
	{
		cout<<"["<<newPath[i].first<<","<<newPath[i].second<<"] ->";
	}
	cout<<endl;
}

void STC::DFS(Node *node, const Node::Graph& myGraph) {
	int row;
	path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
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
			path.push_back(node->getPosition());
		}
	}
}

void STC::buildFineGraph(const Grid& fineGrid)
{
	//build new fine graph
	buildGraphByGrid(fineGrid, fineGraph);

	buildFinePath();

	//add neighbors for graph
	for(unsigned int i = 0; i< finePath.size()-1; i++)
	{
		fineGraph.at(finePath[i].first).at(finePath[i].second)->addNeighbor(fineGraph.at(finePath[i+1].first).at(finePath[i+1].second));
	}

	//printGraph(fineGraph);
}

//create go&back path from coarse path (for fine path)
void STC::buildFinePath()
{
	int lastDirection, direction;
	unsigned int i;

	//build fine path
	// 1= up, 2= down, 3= left, 4= right
	lastDirection = 0;

	for(i = 0; i< path.size()-1; i++)
	{
		direction = getNextDirection(path[i], path[i+1]);
		switch(direction)
		{
		case MOVING_UP: // up
			if(lastDirection == MOVING_RIGHT) //up from right
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2)); //add down left
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2+1)); //add down right
				finePath.push_back(Position(path[i].first*2, path[i].second*2+1)); //add upper right
			}
			else if(lastDirection == MOVING_DOWN) // from down to up -> U TURN
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2)); //add up left
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2)); //add down left
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2 +1)); //add down right
				finePath.push_back(Position(path[i].first*2, path[i].second*2 +1)); //add up right
			}
			else if(lastDirection == MOVING_LEFT) //from left to up
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2 +1));
			}
			else //continue moving up
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2 +1));
				finePath.push_back(Position(path[i].first*2 , path[i].second*2 +1));
			}
			lastDirection = direction;
			break;
		case MOVING_DOWN: // down

			if(lastDirection == MOVING_LEFT) //from left to down
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2+1)); //add upper left
				finePath.push_back(Position(path[i].first*2, path[i].second*2)); //add upper right
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2)); //add down left
			}
			else if(lastDirection == MOVING_UP) //from up to down -> U TURN
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2+1)); // add down right
				finePath.push_back(Position(path[i].first*2, path[i].second*2+1)); //add up right
				finePath.push_back(Position(path[i].first*2, path[i].second*2)); //add up left
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2)); //add down left

			}
			else if(lastDirection == MOVING_RIGHT) //from right to down
			{
				finePath.push_back(Position(path[i].first*2+1, path[i].second*2)); //add down left
			}
			else // continue moving down
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2)); //add up left
				finePath.push_back(Position(path[i].first*2+1, path[i].second*2)); // add down left
			}
			lastDirection = direction;
			break;
		case MOVING_LEFT: // left

			if(lastDirection == MOVING_UP) // from up to left
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2+1));
				finePath.push_back(Position(path[i].first*2, path[i].second*2));
			}
			else if(lastDirection == MOVING_RIGHT) // from right to left -> U TURN
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2));
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2+1));
				finePath.push_back(Position(path[i].first*2, path[i].second*2 +1));
				finePath.push_back(Position(path[i].first*2, path[i].second*2));
			}
			else if(lastDirection == MOVING_DOWN) //from down to left
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2));
			}
			else //continue go left
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2+1)); //add up left
				finePath.push_back(Position(path[i].first*2, path[i].second*2)); // add up right
			}
			lastDirection = direction;
			break;
		case MOVING_RIGHT: //right
			if(lastDirection == MOVING_DOWN) // from down to right
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2)); //add down left
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2+1)); //add down right
			}
			else if(lastDirection == MOVING_LEFT) // from left to right -> U TURN
			{
				finePath.push_back(Position(path[i].first*2, path[i].second*2 +1));
				finePath.push_back(Position(path[i].first*2, path[i].second*2));
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2));
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2 +1));
			}
			else if(lastDirection == MOVING_UP) //from up to right
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2 +1));
			}
			else //continue moving right
			{
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2));
				finePath.push_back(Position(path[i].first*2 +1, path[i].second*2+1));
			}
			lastDirection = direction;
			break;
		}

	}
}

int STC::getNextDirection(const Position currentPos, const Position nextPosition)
{
	if(currentPos.first > nextPosition.first)
	{
		//going up
		return MOVING_UP;
	}
	else if(currentPos.first < nextPosition.first)
	{
		//going down
		return MOVING_DOWN;
	}
	else
	{
		if(currentPos.second > nextPosition.second)
		{
			//going left
			return MOVING_LEFT;
		}
		else if(currentPos.second <= nextPosition.second)
		{
			//going right
			return MOVING_RIGHT;
		}
	}
	return 0;
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

STC::~STC() {
	for(int i= 0; i<(int)coarseGraph.size(); i++)
		for(int j=0; j<(int)coarseGraph[0].size(); j++)
			delete(coarseGraph[i][j]);
	coarseGraph.clear();
	path.clear();
	finePath.clear();
}
