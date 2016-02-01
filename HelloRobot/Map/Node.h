/*
 * Node.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <iostream>
using namespace std;

typedef pair<int, int> Position;


class Node {
private:


public:
	vector<Node *> neighborsInTree;
	int row, col;
	bool visited;
	bool isWall;
	Node* cameFrom;
	typedef vector<vector<Node*> > Graph;

	Node(int row, int col, bool isWall);
	Position getPosition();
	void setCameFrom(Node* father) {cameFrom = father;}
	void addNeighbor(Node* newNeighbor);
	virtual ~Node();
};

#endif /* NODE_H_ */
