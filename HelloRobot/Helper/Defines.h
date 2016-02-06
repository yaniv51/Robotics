/*
 * Defines.h
 *
 *  Created on: Feb 6, 2016
 *      Author: colman
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <vector>

namespace Defines
{
	typedef std::pair<int, int> Position;
	typedef std::vector<Position> Path;
	typedef std::vector<std::vector<bool> > Grid;
	typedef std::pair<int, int> Point;
	typedef std::pair<double, double> xyPosition;
}



#endif /* DEFINES_H_ */
