// Response.h

#ifndef _RESPONSE_h
#define _RESPONSE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ErrorCodes.h"

class ResponseClass
{
 private:
	 Result::ResultCode status;
	 String data;

 public:
	 /*
	Result::ResultCode getStatus() const;		// returns result code, stored in response object
	void setStatus(Result::ResultCode status);	// sets response result code
	void addData(const String &data);			
	void send();								// sends response data to PC
	*/
};

#endif

