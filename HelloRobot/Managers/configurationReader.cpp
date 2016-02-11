/*
 * configurationReader.cpp
 *
 *  Created on: Feb 11, 2016
 *      Author: colman
 */

#include "configurationReader.h"

configurationReader::configurationReader() {
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

			//cout << tokens.size() << endl;
			if (token == "map") {
				map_path = tokens[0];
				//cout << "the map path is : " + map_path + "\n";
			} else if (token == "startLocation") {
				//cout << "hi2" << endl;
				//cout << tokens[0] << endl;
				//cout << tokens[1] << endl;
				//cout << tokens[2] << endl;

				startLocation_X = atoi(tokens[0].c_str());
				startLocation_Y = atoi(tokens[1].c_str());
				startLocation_Yaw = atoi(tokens[2].c_str());

				cout << startLocation_X << endl;
				cout << startLocation_Y << endl;
				cout << startLocation_Yaw << endl;

			} else if (token == "robotSize") {
				robotSize = atof(tokens[0].c_str());
				cout << "robotsize" << robotSize << endl;
			} else if (token == "MapResolutionCM") {
				MapResolutionCM = atof(tokens[0].c_str());
				cout << MapResolutionCM << endl;
			}
		}
	}
	myfile.close();
}

