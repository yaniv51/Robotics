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

	//printGrid(map);
	inflateObstacles();
	createFineGrid();
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
	Grid copy = copyGrid(map);
	int rows =map.size();
		int cols = map[0].size();
		for (int i=0; i < rows; i++){
			for (int j = 0; j < cols; j++){
				if(copy[i][j]==true)
					inflationCell(map, i, j, inflationRadius);
			}
		}
		printGrid(map);
}

void Map::createFineGrid()
{
	int totalFineRows, totalFineColumns, i, j, currentFineRows, currentFineColumns;
	bool foundObstacle;

	totalFineRows =(map.size()/robotSizeInCells);
	totalFineColumns =(map[0].size()/robotSizeInCells);
	//resize grid
	fineGrid.resize(totalFineRows);
	for(int i=0;i<totalFineRows;i++)
		fineGrid[i].resize(totalFineColumns);
	cout<<"robot size in cell: "<<robotSize<<endl;
	cout<<"fine grid size: rows: "<<totalFineRows<<" columns: "<<totalFineColumns<<endl;

	currentFineColumns = 0;
	currentFineRows = 0;

	for(i = 0; i<(int)(map.size()-robotSizeInCells); i+=robotSizeInCells)
	{
		for(j= 0; j< (int)(map[0].size()-robotSizeInCells); j+=robotSizeInCells)
		{
			foundObstacle = isFindAreaOccupied(i, j);

			if(currentFineColumns < totalFineColumns)
			{
				fineGrid[currentFineRows][currentFineColumns] = foundObstacle;
				currentFineColumns++;
			}
			else
			{
				currentFineColumns = 0;
				currentFineRows++;
				if(currentFineRows >= totalFineRows)
					break;
				fineGrid[currentFineRows][currentFineColumns] = foundObstacle;
			}
		}
	}
	printGrid(fineGrid);
}

bool Map::isFindAreaOccupied(int row, int column)
{
	int i, j;
	bool foundObstacle;

	foundObstacle = false;
	for(i = 0; i <robotSizeInCells; i++)
	{
		for(j = 0; j < robotSizeInCells; j++)
		{
				if(map[row+i][column+j]==true)
				{
					foundObstacle=true;
					break;
				}
		}
		if(foundObstacle)
			break;
	}

	return foundObstacle;
}

Grid Map::copyGrid(const Grid &grid)
{
	Grid copy;
	copy.resize(map.size());
	for (unsigned int i = 0; i < mapHeight; i++)
		copy[i].resize(map[i].size());

	for (unsigned int i = 0; i < mapHeight; i++) {
		for (unsigned int j = 0; j < mapWidth; j++) {
			copy[i][j] = map[i][j];
		}
	}

	return copy;
}

bool Map::checkIdBorderValid(int row,int column)
{
	if(row <= (int)map.size()-1 && column <= (int)map[row].size()-1 && row>=0 && column>=0)
		return true;
	else
		return false;
}

void Map::inflationCell(Grid &newMap, int row, int column, int radius)
{
	for(int k=1;k<=radius ;k++)
	{
			if(checkIdBorderValid(row,column+k)==true )
				map[row][column+k]=true;
			if(checkIdBorderValid(row,column-k)==true )
				map[row][column-k]=true;
			if(checkIdBorderValid(row+k,column)==true )
					map[row+k][column]=true;
			if(checkIdBorderValid(row-k,column)==true )
					map[row-k][column]=true;
			if(checkIdBorderValid(row+k,column+k)==true )
					map[row+k][column+k]=true;
			if(checkIdBorderValid(row-k,column-k)==true )
				map[row-k][column-k]=true;
			if(checkIdBorderValid(row+k,column-k)==true )
					map[row+k][column-k]=true;
			if(checkIdBorderValid(row-k,column+k)==true )
					map[row-k][column+k]=true;
	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub

	// delete[] image????
}

