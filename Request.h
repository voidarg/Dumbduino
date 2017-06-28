// Request.h

#ifndef _REQUEST_h
#define _REQUEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// forward declarations for supported
class RequestClass;
class MoveRequestClass;
class PositionRequestClass;

class RequestHandlerClass
{
 private:
	 static RequestClass* receiving; // request, currently being received

	 // supported requests
	 static MoveRequestClass move;		// request to move motor
	 static PositionRequestClass position;	// request to

 public
};


class RequestClass
{
};


class MoveRequestClass : RequestClass
{
private:
public:
	virtual bool readNext()
	{


	}
};

class PositionRequestClass : RequestClass
{
private:
public:
};

#endif

