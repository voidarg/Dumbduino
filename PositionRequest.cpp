// 
// 
// 
#include "ErrorCodes.h"
#include "RequestFormat.h"
#include "RobotControl.h"
#include "PositionRequest.h"

void PositionRequest_P::clear()
{
	step = 0;
	motor = 0;
}

Result::ResultCode PositionRequest_P::process()
{
	switch (step)
	{
	case 0:		// receiving motor id
	{
    Serial.print("*PR1");
		return readMotorId();
	}
	default:	// receiving closing tag
	{
  Serial.print("*PR2");
		Result::ResultCode res = readClosingTag();
		if (Result::Success == res) {
			return execute();
		}
		else {
			return res;
		}
	}
	}
}

inline Result::ResultCode PositionRequest_P::readMotorId()
{
	Result::ResultCode ret = RequestFormat::readAndValidateByte(0, 5, motor);
	if (ret == Result::Pending) {
		++step;
	}
	return  ret;
}

inline Result::ResultCode PositionRequest_P::readClosingTag()
{
	Result::ResultCode ret = RequestFormat::readDelimiter(RequestFormat::EndChar);
	if (ret == Result::Pending) {
		++step;
	}
	return ret;
}

inline Result::ResultCode PositionRequest_P::execute()
{
	int pos;
	Result::ResultCode res = RobotControl.getPosition(motor, pos);
	if (res == Result::Success) {
		Serial.print("{M:");
		Serial.print(motor, DEC);
		Serial.print("P:");
		Serial.print(pos, DEC);
		Serial.print("}");
	}
	return res;
}


