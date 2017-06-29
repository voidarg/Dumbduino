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
	virtual Result::ResultCode process();

protected:
	virtual void clear();

private:
	Result::ResultCode readMotorId();
	Result::ResultCode readDelimiter();
	Result::ResultCode readDirection();
	Result::ResultCode readSpeed();
	Result::ResultCode readClosingTag();
	Result::ResultCode execute();

private:
	byte step;
	byte motor;
	char direction;
	byte speed;
};

#endif

