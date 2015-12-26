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

typedef pair<int, int> Point;

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
	void inflationCell(Grid &newMap, int row, int column, int radius);
	void inflationRectangle(Grid &newMap, Point point1, Point point2);

	bool checkIfCellIsOccupied(int i, int j);
	void printGrid(const Grid &grid) const;

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath);
	void inflateObstacles();
	virtual ~Map();
};

#endif /* MAP_H_ */
