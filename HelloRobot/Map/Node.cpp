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
}

void Node::addNeighbor(Node* newNeighbor)
{
	neighborsInTree.push_back(newNeighbor);
}

Position Node::getForwardPosition()
{
	Position pos(row*2, col*2);
	return pos;
}

Position Node::getBackwardPosision()
{
	Position pos(row*2 +1, col*2 +1);
	return pos;
}

Position Node::getPosition()
{
	Position pos(row, col);
	return pos;
}

Node::~Node() {

}

