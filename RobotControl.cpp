// 
// 
// 

#include "RobotControl.h"

void RobotControlClass::init()
{
	// initialize kinematic chains
	kinematicChains[0].init(2, 3, A0);
	kinematicChains[1].init(4, 5, A1);
	kinematicChains[2].init(7, 6, A2);
	kinematicChains[3].init(8, 9, A3);
	kinematicChains[4].init(12, 10, A4);
	kinematicChains[5].init(13, 11, A5);
}

void RobotControlClass::processCommand(byte *buffer)
{
	if (buffer[0] == 'M') {
		// move
		byte motor = buffer[1];
		byte direction = buffer[2];
		byte speed = buffer[3];

		if (motor >= 0 && motor < 6) {
			kinematicChains[motor].move(direction, speed);
		}
	}
}

RobotControlClass RobotControl;

