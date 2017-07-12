// MoveRequestClass.h

#ifndef _MOVEREQUESTCLASS_h
#define _MOVEREQUESTCLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IRequest.h"

class MoveRequest_M : public IRequest
{
public:
	enum { RequestId = 'M' };
	virtual ResultClass::ResultCode process() final;
	virtual void clear() final;

private:
	ResultClass::ResultCode readMotorId();
	ResultClass::ResultCode readDelimiter();
	ResultClass::ResultCode readDirection();
	ResultClass::ResultCode readSpeed();
	ResultClass::ResultCode readClosingTag();
	ResultClass::ResultCode execute();

private:
	byte step;
	byte motor;
	char direction;
	byte speed;
};

#endif

