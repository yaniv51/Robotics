/*
 * MoveLeft.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#include "MoveLeft.h"

MoveLeft::MoveLeft(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub

}

bool MoveLeft::startCond()
{
	return _robot->canRotate();
}

bool MoveLeft::stopCond()
{
	bool result;

	result = !_robot->canRotate() || _robot->canMoveForward();

	/*if (result)
	{
		_robot->SetSpeed(0.0, 0.0);
	}*/

	return result;
}
void MoveLeft::action()
{
	_robot->SetSpeed(0.0,LEFT_ANGULAR_SPEED);
}

MoveLeft::~MoveLeft() {
	// TODO Auto-generated destructor stub
}

