// Arm.h

#ifndef _ARM_h
#define _ARM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ArmClass
{
 protected:


 public:
	void init();
};

extern ArmClass Arm;

#endif

