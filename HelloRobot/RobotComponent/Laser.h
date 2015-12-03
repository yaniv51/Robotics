/*
 * Laser.h
 *
 *  Created on: Nov 25, 2015
 *      Author: israelya
 */

#ifndef LASER_H_
#define LASER_H_
#include <libplayerc++/playerc++.h>
#include <iostream>

#define MAX_

using namespace std;
using namespace PlayerCc;

class Laser {
private:
	LaserProxy* lp;
	int lastObstacleIndex;
public:
	Laser(LaserProxy* laser);
	double ConverIndexToDegree(int index);
	int ConvertDegreeToIndex(double degree);
	bool CanMoveForward();
	double GetRightRank();
	double GetLeftRank();
	int GetLastObstacleIndex() {return lastObstacleIndex;}

	virtual ~Laser();
};

#endif /* LASER_H_ */
