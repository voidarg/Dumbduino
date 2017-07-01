// PositionRequest.h

#ifndef _POSITIONREQUEST_h
#define _POSITIONREQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IRequest.h"

class PositionRequest_P : public IRequest
{
public:
	enum { RequestId = 'P' };
	virtual Result::ResultCode process() final;
	virtual void clear() final;

private:
	Result::ResultCode execute();

private:
	byte motor;
	byte step;
};

#endif

