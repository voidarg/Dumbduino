// PositionRequest.h

#ifndef _POSITIONREQUEST_h
#define _POSITIONREQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IRequest.h"

class PositionRequest_P : public virtual IRequest
{
public:
	enum { RequestId = 'P' };
	virtual Result::ResultCode process();

protected:
	virtual void clear();

private:
	Result::ResultCode readMotorId();
	Result::ResultCode readClosingTag();
	Result::ResultCode execute();

private:
	byte motor;
	byte step;
};

#endif

