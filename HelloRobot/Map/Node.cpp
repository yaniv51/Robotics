/*
 * Node.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "Node.h"

Node::Node(int row, int col, bool isWallT) : row(row), col(col)
{
	isWall = isWallT;
	visited = false;
	cameFrom = NULL;
	//cout<<"create node: "<<row<<","<<col<<"is wall: "<<isWallT<<endl;
}

vector<Node*> Node::getAllPossibleMves(const Graph& map)
{
	if(neighborsInTree.size() > 0)
		return neighborsInTree;
	//cout<<"("<<row<<","<<col<<")"<<" neighbors: ";

	//left
	if(col-1 > -1)
	{
		if(!(map.at(row).at(col-1)->isWall) && !(map.at(row).at(col-1)->visited))
		{
			neighborsInTree.push_back(map.at(row).at(col-1));
			map.at(row).at(col-1)->setCameFrom(this);
			//cout<<","<<"("<<row<<","<<(col-1)<<")";
		}
	}

	//up
	if(row-1 > -1)
	{
		if(!(map.at(row-1).at(col)->isWall) && !(map.at(row-1).at(col)->visited))
		{
			neighborsInTree.push_back(map.at(row-1).at(col));
			map.at(row-1).at(col)->setCameFrom(this);
			//cout<<","<<"("<<row-1<<","<<col<<")";
		}
	}

	//down
	if(row+1 < (int)map.size())
	{
		if(!(map.at(row+1).at(col)->isWall) && !(map.at(row+1).at(col)->visited))
		{
			neighborsInTree.push_back(map.at(row+1).at(col));
			map.at(row+1).at(col)->setCameFrom(this);
			//cout<<","<<"("<<row+1<<","<<col<<")";
		}
	}

	//right
	if(col+1 < (int)map[0].size())
	{
		if(!(map.at(row).at(col+1)->isWall) && !map.at(row).at(col+1)->visited)
		{
			neighborsInTree.push_back(map.at(row).at(col+1));
			map.at(row).at(col+1)->setCameFrom(this);
			//cout<<","<<"("<<row<<","<<(col+1)<<")";
		}
	}

	//cout<<endl;
	return neighborsInTree;
}

Position Node::getPosition()
{
	Position pos(row, col);
	return pos;
}

Node::~Node() {

}

