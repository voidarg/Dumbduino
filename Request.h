// Request.h

#ifndef _REQUEST_h
#define _REQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MoveRequest.h"
#include "PositionRequest.h"
#include "IRequest.h"

class RequestClass :
	private virtual MoveRequest_M,
	private virtual PositionRequest_P
{
public:
	virtual void reset();
	void init();
	virtual ResultClass::ResultCode processNext();

private: 
	void selectInterface(char id);

private:
	bool receiving;
	IRequest* current;
	ResultClass::ResultCode status;
};

extern RequestClass Request;
#endif

