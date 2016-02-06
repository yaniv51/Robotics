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

	double ConvertRobotLocationToMapPixel(double size, double robotMapSize, double startPos);
}



#endif /* MATHHELPER_H_ */
