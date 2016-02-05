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

	//printGrid(map);
	inflateObstacles();
	//printGrid(map);
	createFineGrid();
	printGrid(fineGrid);
	createCoarseGrid();
	printGrid(coarseGrid);
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
	//x/=2;
	//y/=2;
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

void Map::addPathToFile(const char* filePath , Node::Graph graph,int Width,int Hight) {
	cout<<"file path " <<filePath<<endl;
	cout<<"Width " << Width << endl;
	cout<<"Height " << Hight <<endl;
	cout<<"Graph length " << graph.size()<<endl;
	for(int z = Hight-1;z>-1;z--){
		for(int l= Width-1;l>-1;l--){
			if (graph.size()>(unsigned)z && graph[0].size()>(unsigned)l && graph[z][l] != NULL) {
				for (int k=0;k<4;k++) {
					if ( (graph[z][l]->neighborsInTree.size() > (unsigned)k) && (graph[z][l]->neighborsInTree[k] != NULL)) {
						int i = graph[z][l]->getPosition().first;
						int j = graph[z][l]->getPosition().second;
						//convert the row to the original map row that was read from the image
						i = ((i+0.5) * robotSizeInCells * 2);
						//convert the row to the original map column that was read from the image
						j = ((j+0.5) * robotSizeInCells * 2);
						int i1 = graph[z][l]->neighborsInTree[k]->getPosition().first;
						int j1 = graph[z][l]->neighborsInTree[k]->getPosition().second;
						////convert the row to the original map row that was read from the image
						i1 = ((i1+0.5) * robotSizeInCells * 2);
						////convert the row to the original map column that was read from the image
						j1 = ((j1+0.5) * robotSizeInCells * 2);
						//check how we need to move on row or column
						if(j<j1 && i == i1){
							for (int m = j; m < j1; m++) {
								int c = (i * mapWidth + m) * 4;
								image[c] = 255;
								image[c + 1] = 0;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j>j1 && i == i1){
							for (int m =j1 ; m < j; m++) {
								int c = (i * mapWidth + m) * 4;
								image[c] = 255;
								image[c + 1] = 0;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j == j1 && i > i1){
							for (int m =i1 ; m < i; m++) {
								int c = (m * mapWidth + j) * 4;
								image[c] = 255;
								image[c + 1] = 0;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j == j1 && i < i1){
							for (int m =i ; m < i1; m++) {
								int c = (m * mapWidth + j) * 4;
								image[c] = 255;
								image[c + 1] = 0;
								image[c + 2] = 0;
							}
						}
						//cout << "(" << graph[z][l]->getPosition().first << "," << graph[z][l]->getPosition().second << ")";
						//cout << " -> ";
						//cout << "(" << graph[z][l]->neighborsInTree[k]->getPosition().first << "," << graph[z][l]->neighborsInTree[k]->getPosition().second << ")" << endl;
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

//test
void Map::addFullPathToFile(const char* filePath, Path path, int Width,int Hight)
{
	int location = -1; //each location mak sign = >  0 = left , 1 =  right , 2 = down, 3 = up

	for (unsigned int z = 0; z < path.size()-1; z++) {
		int this_x = path[z].first;
		int this_y = path[z].second;
		int next_x = path[z+1].first;
		int next_y = path[z+1].second;

		/*int this_x = path[z].second;
		int this_y = path[z].first;
		int next_x = path[z+1].second;
		int next_y = path[z+1].first;*/

		//convert the row to the original map row that was read from the image
		next_x = ((next_x + 0.5) * robotSizeInCells * 2);
		//convert the row to the original map column that was read from the image
		next_y = ((next_y + 0.5) * robotSizeInCells * 2);
		////convert the row to the original map row that was read from the image
		this_x = ((this_x + 0.5) * robotSizeInCells * 2);
		////convert the row to the original map column that was read from the image
		this_y = ((this_y + 0.5) * robotSizeInCells * 2);
		//checking the current position to the next position

		//Going right
		if (this_y < next_y && this_x == next_x) {

			if (location == 2) {//from down to right
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));

			} else if (location == 0) {// U TURN!!
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
			}
			drawline(this_x,this_y,next_x,next_y);
			addWayPoint(next_x + (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells));
			this->drawline(this_x + (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),next_x + (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells));
			location = 1;

			//Going left
		} else if (this_y > next_y && this_x == next_x) {
			if (location == 3) {// from up to left
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
			} else if (location == 1) {// U TURN!!
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
			}
			drawline(this_x,this_y,next_x,next_y);
			addWayPoint(next_x - (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells));
			this->drawline(this_x - (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),next_x - (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells));
			location = 0;

			//Going up
		} else if (this_y == next_y && this_x > next_x) {

			if (location == 1) {// up from right
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
			} else if (location == 2) {// U TURN!!
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells));
			}
			drawline(this_x,this_y,next_x,next_y);
			addWayPoint(next_x + (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells));
			this->drawline(this_x - (0.5 * robotSizeInCells), this_y + (0.5 * robotSizeInCells),next_x + (0.5 * robotSizeInCells),next_y + (0.5 * robotSizeInCells));
			location = 3;
			//Going down
		} else if (this_y == next_y && this_x < next_x) {

			if (location == 0) {// from left to down
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells),this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
			} else if (location == 3) {// U TURN!!
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				addWayPoint(this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				addWayPoint(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
				this->drawline(this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y - (0.5 * robotSizeInCells));
				this->drawline(this_x + (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells),this_x - (0.5 * robotSizeInCells),this_y + (0.5 * robotSizeInCells));
			}

			drawline(this_x,this_y,next_x,next_y);
			this->drawline(this_x + (0.5 * robotSizeInCells), this_y - (0.5 * robotSizeInCells),next_x - (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells));
			addWayPoint(next_x - (0.5 * robotSizeInCells),next_y - (0.5 * robotSizeInCells));

			location = 2;
		}

	}
	lodepng::encode(filePath, image, mapWidth, mapHeight);
}
//test
void Map::addWayPoint(int x, int y)
{

}
//test
void Map::addFinePathToFile(const char* filePath, Node::Graph graph,int Width,int Hight)
{
	cout<<"file path " <<filePath<<endl;
	cout<<"Width " << Width << endl;
	cout<<"Height " << Hight <<endl;
	cout<<"Graph length " << graph.size()<<endl;
	for(int z = Hight-1;z>-1;z--){
		for(int l= Width-1;l>-1;l--){
			if (graph.size()>(unsigned)z && graph[0].size()>(unsigned)l && graph[z][l] != NULL) {
				for (int k=0;k<4;k++) {
					if ( (graph[z][l]->neighborsInTree.size() > (unsigned)k) && (graph[z][l]->neighborsInTree[k] != NULL)) {
						int i = graph[z][l]->getPosition().first;
						int j = graph[z][l]->getPosition().second;
						//convert the row to the original map row that was read from the image
						i = ((i+0.5) * robotSizeInCells);
						//convert the row to the original map column that was read from the image
						j = ((j+0.5) * robotSizeInCells);
						int i1 = graph[z][l]->neighborsInTree[k]->getPosition().first;
						int j1 = graph[z][l]->neighborsInTree[k]->getPosition().second;
						////convert the row to the original map row that was read from the image
						i1 = ((i1+0.5) * robotSizeInCells);
						////convert the row to the original map column that was read from the image
						j1 = ((j1+0.5) * robotSizeInCells);
						//check how we need to move on row or column
						if(j<j1 && i == i1){
							for (int m = j; m < j1; m++) {
								int c = (i * mapWidth + m) * 4;
								image[c] = 0;
								image[c + 1] = 255;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j>j1 && i == i1){
							for (int m =j1 ; m < j; m++) {
								int c = (i * mapWidth + m) * 4;
								image[c] = 0;
								image[c + 1] = 255;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j == j1 && i > i1){
							for (int m =i1 ; m < i; m++) {
								int c = (m * mapWidth + j) * 4;
								image[c] = 0;
								image[c + 1] = 255;
								image[c + 2] = 0;
							}
							//check how we need to move on row or column
						}else if(j == j1 && i < i1){
							for (int m =i ; m < i1; m++) {
								int c = (m * mapWidth + j) * 4;
								image[c] = 0;
								image[c + 1] = 255;
								image[c + 2] = 0;
							}
						}
						//cout << "(" << graph[z][l]->getPosition().first << "," << graph[z][l]->getPosition().second << ")";
						//cout << " -> ";
						//cout << "(" << graph[z][l]->neighborsInTree[k]->getPosition().first << "," << graph[z][l]->neighborsInTree[k]->getPosition().second << ")" << endl;
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
//test
void Map::drawline(int x1, int y1, int x2, int y2)
{
	//left or right
	if (x1 == x2) {

		for (int m = y1; m < y2; m++) {
			int c = (x1 * mapWidth + m) * 4;
			image[c] = 255;
			image[c + 1] = 0;
			image[c + 2] = 0;
		}
		//up or down
	}else if (y1 == y2 ) {
		for (int m = x2; m < x1; m++) {
			int c = (m * mapWidth + y1) * 4;
			image[c] = 255;
			image[c + 1] = 0;
			image[c + 2] = 0;
		}
	}
}

Map::~Map() {
	map.clear();
	fineGrid.clear();
	coarseGrid.clear();
}

