// 
// 
// 

#include "ErrorCodes.h"
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

Result::ResultCode RobotControlClass::move(byte motor, byte direction, byte speed)
{
	if (motor < 0 || motor > 5)
		return Result::ParameterOutOfRange;

	kinematicChains[motor].move(direction, speed);
	return Result::Success;
}

Result::ResultCode RobotControlClass::getPosition(byte motor, int &position)
{
	if (motor < 0 || motor > 5)
		return Result::ParameterOutOfRange;

	position = kinematicChains[motor].readPosition();
	return Result::Success;
}

RobotControlClass RobotControl;

