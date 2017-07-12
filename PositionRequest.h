// PositionRequest.h

#ifndef _POSITIONREQUEST_h
#define _POSITIONREQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IRequest.h"
#include "ErrorCodes.h"

class PositionRequest_P : public IRequest
{
public:
	enum { RequestId = 'P' };
	virtual ResultClass::ResultCode process() final;
	virtual void clear() final;

private:
	ResultClass::ResultCode execute();

private:
	byte motor;
	byte step;
};

#endif

