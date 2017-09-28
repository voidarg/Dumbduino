#include "Response.h"
#include "Diagnostics.h"
#include "RequestReader.h"
#include "RequestReader.h"
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
}

void serialEvent()
{
	// read positions
//	if (Serial.available()) {
		ResultClass::ResultCode res = Request.processNext();
		if (res >= ResultClass::Success) {
			Request.reset();
			//Serial.print("<");
			//Serial.print(res, DEC);
			//Serial.print(">");
		}
	//}

}
