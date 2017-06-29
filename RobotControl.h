// RobotControl.h

#ifndef _ROBOTCONTROL_h
#define _ROBOTCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "KinematicChain.h"

class RobotControlClass
{
 protected:
	 KinematicChainClass kinematicChains[6];

 public:
	void init();
	Result::ResultCode move(byte motor, byte direction, byte speed);
	Result::ResultCode getPosition(byte motor, int &position);
};

extern RobotControlClass RobotControl;

#endif

