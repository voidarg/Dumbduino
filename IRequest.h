
#ifndef _IREQUEST_h
#define _IREQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

struct IRequest
{
public:
	virtual Result::ResultCode process() = 0;

protected:
	virtual void clear() = 0;
};

#endif
