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

	double ConvertMapPixelToY(double robotMapResolution, double robotMapSize, double yPixel);
	double ConvertMapPixelToX(double robotMapResolution, double robotMapSize, double xPixel);
}



#endif /* MATHHELPER_H_ */
