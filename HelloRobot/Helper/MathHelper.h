/*
 * MathHelper.h
 *
 *  Created on: Nov 30, 2015
 *      Author: colman
 */

#ifndef MATHHELPER_H_
#define MATHHELPER_H_
#include "math.h"

namespace MathHelper
{
	double ConvertDegreeToRadian(double degree);

	double ConvertRadianToDegree(double radian);

	double ConvertYRobotLocationToMapPixel(double robotMapResolution, double robotMapSize, double y);

	double ConvertXRobotLocationToMapPixel(double robotMapResolution, double robotMapSize, double x);
}



#endif /* MATHHELPER_H_ */
