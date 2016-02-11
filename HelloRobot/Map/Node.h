/*
 * Node.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include "../Helper/Defines.h"
#include <iostream>

using namespace std;
using namespace Defines;

class Node {
private:


public:
	typedef vector<vector<Node*> > Graph;
	vector<Node *> neighborsInTree;
	int row, col;
	bool visited;
	bool isWall;
	Node* cameFrom;

	Node(int row, int col, bool isWall);
	Position getPosition();
	void setCameFrom(Node* father) {cameFrom = father;}
	void addNeighbor(Node* newNeighbor);
	virtual ~Node();
};

#endif /* NODE_H_ */
