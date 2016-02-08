/*
 * MathHelper.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: colman
 */

#include "MathHelper.h"
#include <cmath>

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

	double ConvertYRobotLocationToMapPixel(double robotMapResolution, double robotMapSize, double y)
	{
		if(y < 0)
			y = std::abs(y) + (robotMapSize/2);

		// get the relation size of current x from total size (y/0.025)
		return y/robotMapResolution;
	}

	double ConvertXRobotLocationToMapPixel(double robotMapResolution, double robotMapSize, double x)
	{
		if(x<0)
			x = std::abs(x);
		else
			x += (robotMapSize/2); // add half from total size when x is positive number

		// get the relation size of current x from total size (x/0.025)
		return x/robotMapResolution;
	}
}
