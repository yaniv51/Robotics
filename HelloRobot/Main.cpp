#include <iostream>
#include "Robot.h"

using namespace std;

#define HOST_PORT 6665

int main(int argc, char** argv)
{
	Robot myRobot("localhost", HOST_PORT);
	myRobot.StartRobot();
}
