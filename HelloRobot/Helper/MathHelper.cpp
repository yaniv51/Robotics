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

	double ConvertMapPixelToY(double robotMapResolution, double robotMapSize, double yPixel)
	{
		double result;

		result = yPixel*robotMapResolution;

		if(result > robotMapSize/2)
			result =result*(-1) + (robotMapSize/2);

		return result;
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

	double ConvertMapPixelToX(double robotMapResolution, double robotMapSize, double xPixel)
	{
		double result;

		result = xPixel*robotMapResolution;
		if(result< robotMapSize/2) //negetive number
			result*=-1;
		else
			result -= (robotMapSize/2);

		return result;
	}
}
