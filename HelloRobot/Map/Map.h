/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "Node.h";
#include "../Helper/Defines.h"

using namespace std;
using namespace Defines;

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

	void createCoarseGrid();
	void inflationCell(Grid &newMap, int row, int column, int radius);
	bool checkIdBorderValid(int row,int column);
	bool checkIfCellIsOccupied(int i, int j);
	void printGrid(const Grid &grid) const;
	void createFineGrid();
	void createNewGrid(int radiusFactor, Grid& newGrid, const Grid& oldGrid);
	bool isFindAreaOccupied(int row, int column, int radius, const Grid& grid);
	void initializeGrid(int rows, int columns, Grid& grid);
	Grid copyGrid(const Grid &grid);

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath);
	void inflateObstacles();
	Grid& getCoarseGrid(){return coarseGrid;};
	Grid& getFineGrid(){return fineGrid;};
	Point convertPointToFinePoint(int row, int col);
	Point convertPointToCoarsePoint(int row, int col);
	void addPathToFile(const char* filePath, Node::Graph graph,int Width,int Hight, bool coarsePath);
	void setInflationRadius(float value) {inflationRadius = value * robotSizeInCells;}
	virtual ~Map();
};

#endif /* MAP_H_ */
