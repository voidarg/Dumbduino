// 
// 
// 

#include "KinematicChain.h"

void KinematicChainClass::init(byte directionPin, byte movementPin, byte positionPin)
{
	pinMode(directionPin, OUTPUT);
	pinMode(movementPin, OUTPUT);
	pinMode(positionPin, INPUT);
	pinMode(12, OUTPUT);
	digitalWrite(12, 1);
	KinematicChainClass::directionPin = directionPin;
	KinematicChainClass::movementPin = movementPin;
	KinematicChainClass::positionPin = positionPin;
}

void KinematicChainClass::init(byte directionPin, byte movementPin, byte positionPin, int lowerLimit, int upperLimit)
{
	init(directionPin, movementPin, positionPin);
	setLimits(lowerLimit, upperLimit);
}

void KinematicChainClass::setLimits(int lower, int upper)
{
	lowerLimit = lowerLimit;
	upperLimit = upperLimit;
}

void KinematicChainClass::move(byte direction, byte speed)
{
	analogWrite(movementPin, speed);
	digitalWrite(directionPin, direction);
}

inline void KinematicChainClass::stop()
{
	digitalWrite(movementPin, 0);
}

int KinematicChainClass::readPosition()
{
	return analogRead(positionPin);
}
