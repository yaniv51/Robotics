/*
 * MoveRight.h
 *
 *  Created on: Jan 30, 2016
 *      Author: colman
 */

#ifndef MOVERIGHT_H_
#define MOVERIGHT_H_

#include "Behavior.h"

class MoveRight: public Behavior {
public:
	MoveRight(Robot* robot);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~MoveRight();
};

#endif /* MOVERIGHT_H_ */
