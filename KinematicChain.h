// Arm.h

#ifndef _ARM_h
#define _ARM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class KinematicChainClass
{
 private:

	 int upperLimit;
	 int lowerLimit;
	 byte directionPin;
	 byte movementPin;
	 byte positionPin;

 public:
	void init(byte directionPin, byte movementPin, byte positionPin);
	void init(byte directionPin, byte movementPin, byte positionPin, int lowerLimit, int upperLimit);
	void setLimits(int lower, int upper);

		
	void move(byte direction, byte speed);
	inline void stop();
	int readPosition(); // reads current position of the motor
};

#endif

