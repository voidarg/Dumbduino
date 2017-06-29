// RequestFormat.h

#ifndef _REQUESTFORMAT_h
#define _REQUESTFORMAT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ErrorCodes.h"


struct RequestFormat
{
public:
	const static char StartChar = '{';
	const static char EndChar = '}';
	const static char ArgumentDelimiter = ',';

public:
	static Result::ResultCode readAndValidateInt(int min, int max, int& retVal);
	static Result::ResultCode readAndValidateByte(byte min, byte max, byte& retVal);
	static Result::ResultCode readAndValidateFloat(float min, float max, float& retVal);
	static Result::ResultCode readDelimiter(char delimiter);
};


#endif

