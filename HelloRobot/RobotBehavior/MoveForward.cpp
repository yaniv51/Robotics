/*
 * MoveForward.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#include "MoveForward.h"

MoveForward::MoveForward(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub

}

bool MoveForward::startCond()
{
	return _robot->canMoveForward(1.0);
}
bool MoveForward::stopCond()
{
	return !(_robot->canMoveForward(0.8));
}
void MoveForward::action()
{
	_robot->SetSpeed(LINEAR_SPEED,0.0);
}


MoveForward::~MoveForward() {
	// TODO Auto-generated destructor stub
}
