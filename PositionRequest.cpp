// 
// 
// 
#include "ErrorCodes.h"
#include "RequestFormat.h"
#include "RobotControl.h"
#include "PositionRequest.h"
#include "Diagnostics.h"

void PositionRequest_P::clear()
{
	step = 0;
	motor = 0;
}

Result::ResultCode PositionRequest_P::process()
{
	traceln("reading motor id");
	Result::ResultCode res = RequestFormat::readAndValidateByte(0, 5, motor);
	if (Result::Pending == res) {
		trace("read ");
		traceln(motor);
		return execute();
	}
	else {
		return res;
	}
}

inline Result::ResultCode PositionRequest_P::execute()
{
	int pos;
	Result::ResultCode res = RobotControl.getPosition(motor, pos);
	if (res == Result::Success) {
		Serial.print("{M");
		Serial.print(motor, DEC);
		Serial.print(',');
		Serial.print("P");
		Serial.print(pos, DEC);
		Serial.print("}");
	}
	return res;
}


