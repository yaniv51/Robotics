/*
 * configurationReader.h
 *
 *  Created on: Feb 11, 2016
 *      Author: colman
 */


#ifndef CONFIGURATIONREADER_H_
#define CONFIGURATIONREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "../Helper/Defines.h"

using namespace Defines;
using namespace std;

class configurationReader {
public:
	configurationReader();
	string map_path;
	int startLocation_X;
	int startLocation_Y;
	int startLocation_Yaw;
	double robotSize;
	double MapResolutionCM;
	void Read();
	virtual ~configurationReader(){ };

};

#endif /* CONFIGURATIONREADER_H_ */
