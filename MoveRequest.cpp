// 
// 
// 
#include "ErrorCodes.h"
#include "RequestFormat.h"
#include "RobotControl.h"
#include "MoveRequest.h"

void MoveRequest_M::clear()
{
	step = 0;
	motor = 0;
	direction = 0;
	speed = 0;
}

Result::ResultCode MoveRequest_M::process()
{
	switch (step)
	{
	case 0:		// receiving motor id
	{
    Serial.print ("MR1");
		readMotorId();
	}
	case 1:		// receiving first delimiter
	{
    Serial.print ("MR2");
		return readDelimiter();
	}
	case 2:		// receiving direction
	{
    Serial.print ("MR3");
		return readDirection();
	}
	case 3:		// receiving second delimiter
	{
  Serial.print ("MR4");
		return readDelimiter();
	}
	case 4:		// receiving speed
	{
  Serial.print ("MR5");
		return readSpeed();
	}
	default:	// receiving closing tag
	{
  Serial.print ("MR6");
		Result::ResultCode res = readClosingTag();
		if (Result::Success == res) {
    Serial.print ("MR7");
			return execute();
		}
		else {
			return res;
		}
	}
	}
}

inline Result::ResultCode MoveRequest_M::readMotorId()
{
	Result::ResultCode ret = RequestFormat::readAndValidateByte(0, 5, motor);
	if (ret == Result::Pending) {
		++step;
   
	}
	return  ret;
}

inline Result::ResultCode MoveRequest_M::readDelimiter()
{
	Result::ResultCode ret = RequestFormat::readDelimiter(RequestFormat::ArgumentDelimiter);
	if (ret == Result::Pending) {
		++step;
	}
	return ret;
}

inline Result::ResultCode MoveRequest_M::readDirection()
{
	Result::ResultCode ret{Result::Waiting};

	if (Serial.available()) {
		direction = Serial.read();
		if (direction != 'F' && direction != 'B') {
      Serial.print ("*DIR = ");
      Serial.print (direction);
      Serial.println ("*");
			ret = Result::ParameterOutOfRange;
		}
		else {
			++step;
		}
	}
	return ret;
}

inline Result::ResultCode MoveRequest_M::readSpeed()
{
	Result::ResultCode ret = RequestFormat::readAndValidateByte(0, 255, speed);
	if (ret == Result::Pending) {
		++step;
	}
	return  ret;
}

inline Result::ResultCode MoveRequest_M::readClosingTag()
{
	Result::ResultCode ret = RequestFormat::readDelimiter(RequestFormat::EndChar);
	if (ret == Result::Pending) {
		++step;
	}
	return ret;
}

inline Result::ResultCode MoveRequest_M::execute()
{
	Result::ResultCode res = RobotControl.move (
		motor,
		direction == 'F' ? 1 : 0,
		speed);

	return res;
}

