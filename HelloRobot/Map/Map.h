/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
using namespace std;

typedef vector<vector<bool> > Grid;

class Map {
private:
	vector<unsigned char> image;
	Grid map;
	unsigned int mapWidth;
	unsigned int mapHeight;
	float mapResolution;
	float robotSize;
	int robotSizeInCells;
	int inflationRadius;

	Grid fineGrid; // cell size equal to robot size
	Grid coarseGrid; // cell size is 4*robot size

	void buildFineGrid();
	void buildCoarseGrid();

	bool checkIfCellIsOccupied(int i, int j);
	void printGrid(const Grid &grid) const;

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath);
	void inflateObstacles();
	virtual ~Map();
};

#endif /* MAP_H_ */
