/*
 * RobotSettings.h
 *
 *  Created on: Nov 24, 2015
 *      Author: colman
 */

#ifndef ROBOTSETTINGS_H_
#define ROBOSETTINGS_H_

//connection
#define HOST_PORT 6665


#define SAMPLES 666
#define LINEAR_SPEED 0.12
#define LEFT_ANGULAR_SPEED 0.18
#define RIGHT_ANGULAR_SPEED -0.18
#define MIN_DEST_FROM_OBSTACLE 0.6 //check 0.5
#define MAX_RANGE 4.095

#define LASER_RESOLUTION 0.36
#define LASER_MAX_ANGLE 240
#define LASER_MID_ANGLE 120
#define LASER_ARRAY_SIZE 666
//was 270 395
#define LASER_MIN_FORWARD_START_INDEX 266
#define LASER_MIN_FORWARD_END_INDEX 399
#define LASER_MIN_ROTATION_DISTANCE 0.25

#define START_LOCATION_COLUMN 	362
#define START_LOCATION_ROW 		305
//#define MAP_RESOLUTION 0.025
#define MAP_ROW_SIZE 	550
#define MAP_COLUMN_SIZE 380
//#define ROBOT_SIZE 0.3
/*#define ROBOT_START_X 2.175
#define ROBOT_START_Y -2.875
#define ROBOT_START_YAW 45*/

#define MOVING_UP 		1
#define MOVING_DOWN 	2
#define MOVING_LEFT 	3
#define MOVING_RIGHT 	4

#define LOOK_UP 90
#define LOOK_RIGHT 0
#define LOOK_LEFT 180
#define LOOK_DOWN -90

#endif /* ROBOTSETTINGS_H_ */
