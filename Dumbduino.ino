

#include "Response.h"
#include "Diagnostics.h"
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
	// Serial.begin(115200, SERIAL_8O1);
  Serial.begin(115200);

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
	Result::ResultCode res = Request.processNext();
	
	if (res >= Result::Success) {
		Serial.print("<");
		Serial.print(res, DEC);
		Serial.print(">");

		Request.reset();
	}
}
