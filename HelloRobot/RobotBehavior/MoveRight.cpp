/*
 * MoveRight.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#include "MoveRight.h"

MoveRight::MoveRight(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub
}

bool MoveRight::startCond()
{
	return _robot->canRotate();
}

bool MoveRight::stopCond()
{
	bool result;

	result = !_robot->canRotate() || _robot->canMoveForward();

	/*if (result)
	{
		_robot->SetSpeed(0.0, 0.0);
	}*/

	return result;
}
void MoveRight::action()
{
	_robot->SetSpeed(0.0,RIGHT_ANGULAR_SPEED);
}

MoveRight::~MoveRight() {
	// TODO Auto-generated destructor stub
}

