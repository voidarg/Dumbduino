// 
// 
// 
#include "ErrorCodes.h"
#include "RequestFormat.h"
#include "RobotControl.h"
#include "MoveRequest.h"
#include "Diagnostics.h"

void MoveRequest_M::clear()
{
	trace("clearing request");
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
		return readMotorId();
	}
	case 1:		// receiving direction
	{
		return readDirection();
	}
	case 2:		// receiving speed
	{
		Result::ResultCode res = readSpeed();
		if (Result::Pending == res) {
			return execute();
		}
		else {
			return res;
		}
	}
	default:	// receiving closing tag
	{
		trace("NEVER SHOULD GET HERE! Step = ");
		traceln(step);
		
		return Result::CorruptPacket;
	}
	}
}

inline Result::ResultCode MoveRequest_M::readMotorId()
{
	traceln("reading motor id");
	
	Result::ResultCode ret = RequestFormat::readAndValidateByte(0, 5, motor);
	if (ret == Result::Pending) {
		traceln(motor);
		++step;	
	}
	return  ret;
}

inline Result::ResultCode MoveRequest_M::readDelimiter()
{
	traceln("getting deimiter value");
	Result::ResultCode ret = RequestFormat::readDelimiter(RequestFormat::ArgumentDelimiter);
	if (ret == Result::Pending) {
		traceln(ret);
		++step;
	}
	return ret;
}

inline Result::ResultCode MoveRequest_M::readDirection()
{
	Result::ResultCode ret{Result::Waiting};

	traceln("reading direction");
	if (Serial.available()) {
		direction = Serial.read();
		trace("direction received: ");
		traceln(direction);

		if (direction != 'F' && direction != 'B') {
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
	traceln("reading speed");
	Result::ResultCode ret = RequestFormat::readAndValidateByte(0, 255, speed);
	if (ret == Result::Pending) {
		traceln(speed);
		++step;
	}
	return ret;
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

