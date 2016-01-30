/*
 * MoveLeft.h
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#ifndef MOVELEFT_H_
#define MOVELEFT_H_

#include "Behavior.h"

class MoveLeft: public Behavior {
public:
	MoveLeft(Robot* robot);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~MoveLeft();
};

#endif /* MOVELEFT_H_ */
