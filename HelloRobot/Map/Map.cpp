/*
 * Map.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

Map::Map(float mapResolution, float robotSize) :
	mapResolution(mapResolution), robotSize(robotSize) {

	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = 0.3 * robotSizeInCells;
	cout << "inflation radius: " << inflationRadius << endl;

	mapHeight = 0;
	mapWidth = 0;
}

void Map::loadMapFromFile(const char* filePath) {

	lodepng::decode(image, mapWidth, mapHeight, filePath);

	cout << "map size: " << mapWidth << "," << mapHeight << endl;

	map.resize(mapHeight);
	for (unsigned int i = 0; i < mapHeight; i++)
		map[i].resize(mapWidth);

	for (unsigned int i = 0; i < mapHeight; i++) {
		for (unsigned int j = 0; j < mapWidth; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j);
		}
	}

	printGrid(map);
	inflateObstacles();
}

bool Map::checkIfCellIsOccupied(int i, int j) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printGrid(const Grid &grid) const {
	int rows = grid.size();
	int cols = grid[0].size();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (grid[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

void Map::inflateObstacles() {
	//TODO: need to check if realy works (by debug)
	for (unsigned int i = 0; i < mapHeight; i++) {
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			if(map[i][j] == true)
			{
				inflationCell(map, (int)i, (int)j, inflationRadius);
			}
		}
	}
	printGrid(map);
}

void Map::inflationCell(Grid &newMap, int row, int column, int radius)
{
	Point upPoint;
	Point downPoint;

	upPoint.first = row-radius;
	upPoint.second = column-radius;
	if(upPoint.first < 0)
		upPoint.first = 0;
	if(upPoint.second < 0)
		upPoint.second = 0;

	downPoint.first = row+radius;
	downPoint.second = column + radius;
	if(downPoint.first >= (int)mapHeight)
		downPoint.first = (int)mapHeight - 1;
	if(downPoint.second >= (int)mapWidth)
		downPoint.second = (int)mapWidth -1;

	inflationRectangle(newMap, upPoint, downPoint);
}

void Map::inflationRectangle(Grid &newMap, Point point1, Point point2)
{
	for(int i = point1.first; i< point2.first; i++)
		for(int j=point1.first; j<point2.first; j++)
			newMap[i][j] = true;
}

Map::~Map() {
	// TODO Auto-generated destructor stub

	// delete[] image????
}

