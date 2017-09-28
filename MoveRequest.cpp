// 
// 
// 
#include "ErrorCodes.h"
#include "RequestReader.h"
#include "RobotControl.h"
#include "MoveRequest.h"
#include "Diagnostics.h"

void MoveRequest_M::clear()
{
	step = 0;
	motor = 0;
	direction = 0;
	speed = 0;
}

ResultClass::ResultCode MoveRequest_M::process()
{
	Result.reset();
	if (RequestReader.getReadStatus() == RequestReaderClass::ReadStatus::ParamAvailable) {
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
				Result.set (readSpeed());
				if (Result.Succeeded()) {
					return execute();
				}
			}
			default:
			{
				Result.set(ResultClass::CorruptPacket);
			}
		}
	}
	return Result;
}

inline ResultClass::ResultCode MoveRequest_M::readMotorId()
{
	if (RequestReader.getByteParam(motor)) {
		++step;
		Result.set(ResultClass::Success);
	}
	else {
		Result.set(ResultClass::CorruptPacket);
	}
	return Result;
}

inline ResultClass::ResultCode MoveRequest_M::readDirection()
{
	if (RequestReader.getCharParam(direction)) {
		if (direction != 'F' && direction != 'B') {
			Result.set (ResultClass::ParameterOutOfRange);
		}
		else {
			++step;
			Result.reset();
		}
	}
	else {
		Result.set(ResultClass::CorruptPacket);
	}
	return Result;
}

inline ResultClass::ResultCode MoveRequest_M::readSpeed()
{
	if (RequestReader.getByteParam(speed)) {
		++step;
		Result.reset();
	}
	else {
		Result.set(ResultClass::CorruptPacket);
	}
	return Result;
}

inline ResultClass::ResultCode MoveRequest_M::execute()
{
	Result.set(
		RobotControl.move(
			motor,
			direction == 'F' ? 1 : 0,
			speed));
	int pos;
	Result.set(RobotControl.getPosition(motor, pos));
	if (Result.Succeeded()) {
		Serial.print("{M");
		Serial.print(motor, DEC);
		Serial.print(',');
		Serial.print("P");
		Serial.print(pos, DEC);
		Serial.print("}");
	}
	return Result;

}

