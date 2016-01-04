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

class Node {


public:
	typedef vector<vector<Node*> > Graph;

	vector<Node *> neighborsInTree;
	int row, col;
	bool visited;
	bool isWall;
	Node(int row, int col, bool isWall);
	vector<Node*> getAllPossibleMves(const Graph& map);
	virtual ~Node();
};

#endif /* NODE_H_ */
