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
	//inflationRadius = 0.3 * robotSizeInCells;
	cout << "inflation radius: " << inflationRadius << endl;
	cout<<"robot size in cell: "<<robotSizeInCells<<endl;

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

	// inflate map
	inflateObstacles();
	//printGrid(map);

	createFineGrid();
	//printGrid(fineGrid);

	createCoarseGrid();
	//printGrid(coarseGrid);
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

Point Map::convertPointToFinePoint(int col, int row)
{
	int x, y;
	x = row / robotSizeInCells;
	y = col / robotSizeInCells;
	return Point(x, y);
}

Point Map::convertPointToCoarsePoint(int col, int row)
{
	Point newPoint = convertPointToFinePoint(col, row);
	return Point(newPoint.first/2, newPoint.second/2);
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
	int totalFineRows, totalFineColumns;

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
	int totalCoarseRows, totalCoarseColumns, factor;

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
				currentColomn++;
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

	for(i = 0; i<(int)grid.size(); i++)
		for(j=0; j<(int)grid[0].size(); j++)
			grid[i][j] = true;
}

bool Map::isFindAreaOccupied(int row, int column, int radius, const Grid& grid)
{
	int i, j;
	bool foundObstacle;
	foundObstacle = false;

	for(i = 0; i <radius && row+i < (int)grid.size(); i++)
	{
		for(j = 0; j < radius && column+j < (int)grid[j].size(); j++)
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

void Map::addPathToFile(const char* filePath , Node::Graph graph,int Width,int Hight, bool coarsePath) {
	int factor;
	int row, column, neighbors, x, y, x1, y1, m, c;
	int r,g,b;

	cout<<"file path " <<filePath<<endl;
	cout<<"Width " << Width << endl;
	cout<<"Height " << Hight <<endl;
	cout<<"Graph length " << graph.size()<<endl;

	if(coarsePath == true)
	{
		factor = 2;
		r = 255;
		g = 0;
		b = 0;
	}
	else
	{
		factor = 1;
		r = 0;
		g = 255;
		b = 0;
	}

	for(row = Hight-1; row>-1; row--)
	{
		for( column= Width-1; column>-1; column--)
		{
			//check if current point is legal
			if (graph.size()>(unsigned)row && graph[0].size()>(unsigned)column && graph[row][column] != NULL)
			{
				//check for all neighbors
				for (neighbors=0; neighbors<4; neighbors++)
				{
					//check if negibor is valie
					if ((graph[row][column]->neighborsInTree.size() > (unsigned)neighbors) && (graph[row][column]->neighborsInTree[neighbors] != NULL))
					{
						x = graph[row][column]->getPosition().first;
						y = graph[row][column]->getPosition().second;
						//convert row to original map row that was read from the image
						x = ((x+0.5) * robotSizeInCells * factor);
						//convert column to original map column that was read from the image
						y = ((y+0.5) * robotSizeInCells * factor);

						// get negibhor x,y
						x1 = graph[row][column]->neighborsInTree[neighbors]->getPosition().first;
						y1 = graph[row][column]->neighborsInTree[neighbors]->getPosition().second;

						// convert row to original map row that was read from the image
						x1 = ((x1+0.5) * robotSizeInCells * factor);
						//convert column to original map column that was read from the image
						y1 = ((y1+0.5) * robotSizeInCells * factor);
						//check how we need to move on row or column
						if(y<y1 && x == x1){
							for (m = y; m < y1; m++) {
								c = (x * mapWidth + m) * 4;
								image[c] = r;
								image[c + 1] = g;
								image[c + 2] = b;
							}
						}else if(y>y1 && x == x1){
							for (m =y1 ; m < y; m++) {
								c = (x * mapWidth + m) * 4;
								image[c] = r;
								image[c + 1] = g;
								image[c + 2] = b;
							}
						}else if(y == y1 && x > x1){
							for (m =x1 ; m < x; m++) {
								c = (m * mapWidth + y) * 4;
								image[c] = r;
								image[c + 1] = g;
								image[c + 2] = b;
							}
						}else if(y == y1 && x < x1){
							for (m =x ; m < x1; m++) {
								c = (m * mapWidth + y) * 4;
								image[c] = r;
								image[c + 1] = g;
								image[c + 2] = b;
							}
						}
						//cout << "(" << graph[z][l]->getPosition().first << "," << graph[z][l]->getPosition().second << ")";
						//cout << " -> ";
						//cout << "(" << graph[z][l]->neighborsInTree[k]->getPosition().first << "," << graph[z][l]->neighborsInTree[neighbors]->getPosition().second << ")" << endl;
					}
				}
			}
		}
	}
	unsigned error = lodepng::encode(filePath, image, mapWidth, mapHeight);
	if (!error){
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
	}
}

Map::~Map() {
	map.clear();
	fineGrid.clear();
	coarseGrid.clear();
}

