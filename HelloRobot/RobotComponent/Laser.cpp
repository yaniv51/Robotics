/*
 * Laser.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: israelya
 */

#include "Laser.h"
#include "RobotSettings.h"

Laser::Laser(LaserProxy* laser) {
	lp = laser;
	lastObstacleIndex = 0;
}
double Laser::GetLeftRank()
{
	double sum = 0;

	for(unsigned int i = 0; i<=LASER_MIN_FORWARD_START_INDEX; i+=5)
	{
		sum +=(*lp)[i];
	}
	//cout<<"left rank: "<< sum<<endl;
	return sum;
}

double Laser::GetRightRank()
{
	double sum = 0;

	for(unsigned int i = LASER_MIN_FORWARD_END_INDEX; i<LASER_ARRAY_SIZE; i+=5)
	{
		sum +=(*lp)[i];
	}
	//cout<<"right rank: "<< sum<<endl;
	return sum;
}

bool Laser::CanMoveForward(float minForwardDistance)
{
	//double minForwardDistance = 0.5;

	bool canMoveForward = true;
	for (unsigned int index = LASER_MIN_FORWARD_START_INDEX; index < LASER_MIN_FORWARD_END_INDEX; index++)
	{
		double distance = (*lp)[index];
		//cout<<"from ob distance "<<distance<<endl;
		if (distance < minForwardDistance)
		{
			lastObstacleIndex = index;
			canMoveForward = false;
			break;
		}
	}

	return canMoveForward;
}

double Laser::ConverIndexToDegree(int index)
{
	return ( LASER_RESOLUTION * index ) - LASER_MID_ANGLE;
}

int Laser::ConvertDegreeToIndex(double degree)
{
	return ( degree + LASER_MID_ANGLE )/LASER_RESOLUTION;
}

bool Laser::canRotate()
{
	double minRotationDistance ;
	bool canRotate;

	canRotate = true;
	minRotationDistance = LASER_MIN_ROTATION_DISTANCE;

	for (unsigned int index = 0; index < (*lp).GetCount(); index++)
	{
		double distance = (*lp)[index];

		if (distance < minRotationDistance)
		{
			canRotate = false;
			break;
		}
	}

	return canRotate;
}

Laser::~Laser() {

}

