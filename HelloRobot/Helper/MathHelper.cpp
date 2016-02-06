/*
 * MathHelper.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: colman
 */

#include "MathHelper.h"

namespace MathHelper
{
	double ConvertDegreeToRadian(double degree)
	{
		return ( degree * M_PI )/180;
	}

	double ConvertRadianToDegree(double radian)
	{
		return (radian * 180)/M_PI;
	}

	double ConvertRobotLocationToMapPixel(double size, double robotMapSize, double startPos)
	{
		// convert robot x,y to map pixels: ((380.0/9.5)*(9.5/2+2.88)); V (550.0/13.75)*(13.75/2+2.17)); V
		return ((size/robotMapSize) * ((robotMapSize/2)+startPos));
	}
}
