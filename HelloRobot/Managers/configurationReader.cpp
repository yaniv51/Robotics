/*
 * configurationReader.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: colman
 */

#include "configurationReader.h"

configurationReader::configurationReader() {
	startLocation_X = 0;
	startLocation_Y = 0;
	startLocation_Yaw = 0;
	robotSize = 0;
	MapResolutionCM = 0;
}

void configurationReader::Read() {
	string map;
	string line;
	vector<string> tokens;
	string buf; // Have a buffer string
	ifstream myfile("prop");

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			tokens.clear();
			cout << line << '\n';
			string delimiter = ":";
			size_t pos = 0;
			string token;
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			map = line.erase(0, pos + delimiter.length());
			stringstream ss(map);

			while (ss >> buf)
				tokens.push_back(buf);

			if (token == "map") {
				map_path = tokens[0];
			} else if (token == "startLocation") {

				startLocation_X = atoi(tokens[0].c_str());
				startLocation_Y = atoi(tokens[1].c_str());
				startLocation_Yaw = atoi(tokens[2].c_str());

			} else if (token == "robotSize") {
				robotSize = atof(tokens[0].c_str());
			} else if (token == "MapResolutionCM") {
				MapResolutionCM = atof(tokens[0].c_str());
			}
		}
	}
	myfile.close();
}

