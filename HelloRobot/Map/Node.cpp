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
}

vector<Node*> Node::getAllPossibleMves(const Graph& map)
{
	if(row == 10 && col == 7 ){
		int a = 3;
		a++;
	}
	if(neighborsInTree.size() > 0)
		return neighborsInTree;
	cout<<"("<<row<<","<<col<<")"<<" neighbors: ";
	//left
	if(col-1 > -1)
	{
		if(!(map.at(row).at(col-1)->isWall))
		{
			neighborsInTree.push_back(map.at(row).at(col-1));
			cout<<","<<"("<<row<<","<<(col-1)<<")";
		}
	}

	//right
	if(col+1 < (int)map.size())
	{
		//TODO: check for size map
		if(!(map.at(row).at(col+1)->isWall))
		{
			neighborsInTree.push_back(map.at(row).at(col+1));
			cout<<","<<"("<<row<<","<<(col+1)<<")";
		}
	}

	//up
	if(row-1 > -1)
	{
		if(!(map.at(row-1).at(col)->isWall))
		{
			neighborsInTree.push_back(map.at(row-1).at(col));
			cout<<","<<"("<<row-1<<","<<col<<")";
		}
	}

	//down
	if(row+1 < (int)map[0].size())
	{
		if(!(map.at(row+1).at(col)->isWall))
		{
			neighborsInTree.push_back(map.at(row+1).at(col));
			cout<<","<<"("<<row+1<<","<<col<<")";
		}
	}
	cout<<endl;

	return neighborsInTree;
}

Node::~Node() {

}

