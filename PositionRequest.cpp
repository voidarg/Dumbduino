// 
// 
// 
#include "ErrorCodes.h"
#include "RequestReader.h"
#include "RobotControl.h"
#include "PositionRequest.h"
#include "Diagnostics.h"

void PositionRequest_P::clear()
{
	step = 0;
	motor = 0;
}

ResultClass::ResultCode PositionRequest_P::process()
{
	Result.reset();
	if (RequestReader.getReadStatus() == RequestReaderClass::ReadStatus::ParamAvailable) {
		// process parameter here
		if (RequestReader.getByteParam(motor)) {
			Result.set(execute());
		}
		else {
			Result.set(ResultClass::ParameterOutOfRange);
		}
	}
	return Result.get();
}

inline ResultClass::ResultCode PositionRequest_P::execute()
{
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


