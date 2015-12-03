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
}
