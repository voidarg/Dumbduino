
#include "RequestFormat.h"
#include "ErrorCodes.h"
#include "PositionRequest.h"
#include "MoveRequest.h"
#include "Request.h"
#include "RobotControl.h"
#include "Config.h"

void setup()
{
	// initialize robot control
	RobotControl.init();
	Request.init();

	// start serial communication
	Serial.begin(115200, SERIAL_8O1);
}


/****************************************************
 Communication protocol
	
 ****************************************************/
void loop()
{
	// read positions

}

void serialEvent()
{
	Result::ResultCode res = Request.process();

/*	switch (res)
	{
	case Result::Success:
		break;
	case Result::Pending:
		break;
	case Result::Waiting:
		break;
	default:
	}*/
	
	if (res >= Result::Success) {
		Serial.print("<");
		Serial.print(res, DEC);
		Serial.print(">");

		Request.clear();
	}
}
