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
	printGrid(map);
	createFineGrid();
	printGrid(fineGrid);
	//createCoarseGrid();
	//printGrid(coarseGrid);
}

void Map::saveMapToFile(const Grid& grid, const char* path)
{
	/*vector<unsigned char> newImage;

	newImage.resize(grid.size() * grid[0].size() * 4);

	int r, g, b, c;
	for (unsigned int i = 0; i < grid.size(); i++) {
		for (unsigned int j = 0; j < grid[0].size(); j++) {
			{
				c = (i * grid[0].size() + j) * 4;
				if(grid[i][j])
				{
					image[c] = 0;
					image[c+1] = 0;
					image[c+2] = 0;
				}
				else
				{
					image[c] = 255;
					image[c+1] = 255;
					image[c+2] = 255;
				}
			}
		}
	}
	lodepng::encode(path, newImage, grid[0].size(), grid.size());
	lodepng::save_file(newImage, path);*/
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
}

void Map::createFineGrid()
{
	int totalFineRows, totalFineColumns, i;

	totalFineRows =(map.size()/robotSizeInCells);
	totalFineColumns =(map[0].size()/robotSizeInCells);
	cout<<"robot size in cell: "<<robotSize<<endl;
	cout<<"fine grid size: rows: "<<totalFineRows<<" columns: "<<totalFineColumns<<endl;
	//resize grid
	initializeGrid(totalFineRows, totalFineColumns, fineGrid);

	createNewGrid(robotSizeInCells, fineGrid, map);
}

void Map::createCoarseGrid()
{
	int totalCoarseRows, totalCoarseColumns;
	int i, factor;

	factor = 2;
	//building the coarse grid - divide by 2 fine grid for resize map
	totalCoarseRows = fineGrid.size()/factor;
	totalCoarseColumns = fineGrid[0].size()/factor;

	initializeGrid(totalCoarseRows, totalCoarseColumns, coarseGrid);

	cout<<"Coarse grid size: rows: "<<totalCoarseRows<<" columns: "<<totalCoarseColumns<<endl;

	createNewGrid(factor, coarseGrid, fineGrid);
}

void Map::createNewGrid(int radiusFactor, Grid& newGrid, const Grid& oldGrid)
{
	int totalRows, totalColumns, currentRow, currentColomn;
	int i, j;
	int oldRow, oldColumn;
	bool foundObstacle;

	totalRows = newGrid.size();
	totalColumns = newGrid[0].size();

	currentRow = 0;
	currentColomn = 0;

	oldRow = (int)(oldGrid.size() - radiusFactor);
	oldColumn = (int)(oldGrid[0].size() - radiusFactor);
	for(i = 0; i< oldRow; i+=radiusFactor)
	{
		for(j = 0; j<oldColumn; j+=radiusFactor)
		{
			foundObstacle = isFindAreaOccupied(i, j, radiusFactor, oldGrid);

			if(currentColomn < totalColumns)
			{
				newGrid[currentRow][currentColomn] = foundObstacle;
				currentColomn++;
			}
			else
			{
				currentColomn = 0;
				currentRow++;
				if(currentRow >= totalRows)
					break;
				newGrid[currentRow][currentColomn] = foundObstacle;
			}
		}
	}
}

void Map::initializeGrid(int rows, int columns, Grid& grid)
{
	int i, j;
	grid.resize(rows);
	for (i = 0; i < columns; i++)
		grid[i].resize(columns);

	for(i = 0; i<grid.size(); i++)
		for(j=0; j<grid[0].size(); j++)
			grid[i][j] = true;
}

bool Map::isFindAreaOccupied(int row, int column, int radius, const Grid& grid)
{
	int i, j;
	bool foundObstacle;
	foundObstacle = false;

	for(i = 0; i <radius && row+i < grid.size(); i++)
	{
		for(j = 0; j < radius && column+j < grid[j].size(); j++)
		{
				if(grid[row+i][column+j]==true)
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
	copy.resize(grid.size());
	for (unsigned int i = 0; i < mapHeight; i++)
		copy[i].resize(grid[i].size());

	for (unsigned int i = 0; i < mapHeight; i++) {
		for (unsigned int j = 0; j < mapWidth; j++) {
			copy[i][j] = grid[i][j];
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
	map.clear();
	fineGrid.clear();
	coarseGrid.clear();
}

