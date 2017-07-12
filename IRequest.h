
#ifndef _IREQUEST_h
#define _IREQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "RequestReader.h"

struct IRequest
{
public:
	virtual ResultClass::ResultCode process() = 0;
	virtual void clear() = 0;
};

#endif
