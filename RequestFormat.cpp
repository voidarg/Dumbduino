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
 Serial.print ("*parseInt:");
    Serial.print (retVal);
        Serial.println ("*");
	return retVal >= min && retVal <= max ? Result::Success : Result::ParameterOutOfRange;
}

Result::ResultCode RequestFormat::readAndValidateByte(byte min, byte max, byte& retVal)
{
	if (Serial.available() == 0) {
		return Result::Waiting;
	}

	retVal = Serial.parseInt();
	Serial.print ("*parseByte:");
    Serial.print (retVal);
        Serial.println ("*");
	return retVal >= min && retVal <= max ? Result::Pending : Result::CorruptPacket;
}

Result::ResultCode RequestFormat::readAndValidateFloat(float min, float max, float& retVal)
{
	if (Serial.available() == 0) {
		return Result::Waiting;
	}

	retVal = Serial.parseFloat();
 Serial.print ("*parseFloat:");
    Serial.print (retVal);
        Serial.println ("*");
	return retVal >= min && retVal <= max ? Result::Pending : Result::ParameterOutOfRange;
}

Result::ResultCode RequestFormat::readDelimiter(char delimiter)
{
	Result::ResultCode result;
	if (Serial.available())
	{
    char ch = Serial.read();
    Serial.print ("*readDelimiter:");
    Serial.print (ch);
        Serial.println ("*");
		result = (ch == delimiter) ? Result::Pending : Result::CorruptPacket;
	}
	else
	{
		result = Result::Waiting;
	}
	return result;
}

