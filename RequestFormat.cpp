// 
// 
// 

#include "RequestFormat.h"

Result::ResultCode RequestFormat::readAndValidateInt(int min, int max, int& retVal)
{
	if (Serial.available() == 0) {
		return Result::Waiting;
	}
	
	retVal = Serial.parseInt();
	return retVal >= min && retVal <= max ? Result::Success : Result::ParameterOutOfRange;
}

Result::ResultCode RequestFormat::readAndValidateByte(byte min, byte max, byte& retVal)
{
	if (Serial.available() == 0) {
		return Result::Waiting;
	}

	retVal = Serial.parseInt();
	return retVal >= min && retVal <= max ? Result::Pending : Result::CorruptPacket;
}

Result::ResultCode RequestFormat::readAndValidateFloat(float min, float max, float& retVal)
{
	if (Serial.available() == 0) {
		return Result::Waiting;
	}

	retVal = Serial.parseFloat();
	return retVal >= min && retVal <= max ? Result::Pending : Result::ParameterOutOfRange;
}

Result::ResultCode RequestFormat::readDelimiter(char delimiter)
{
	Result::ResultCode result;
	if (Serial.available())
	{
		result = Serial.read() == delimiter ? 
			Result::Pending :
			Result::CorruptPacket;
	}
	else
	{
		result = Result::Waiting;
	}
	return result;
}

