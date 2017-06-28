
#include "Request.h"
#include "RobotControl.h"
#include "Config.h"

void setup()
{
	// initialize robot control
	RobotControl.init();

	// start serial communication
	Serial.begin(115200, SERIAL_8O1);
}


/****************************************************
 Communication protocol is ASCII based

 Commands start with { and end with } characters
 In response to each command, device returns

 MOVE - M:N,D,SSS
	where	M - command id
			N - motor id (0 - 6)
			D - move direction (F/B - FORWARD/BACK)
			SSS - speed value 0 - 255

	returns motor position or error
	{P:N,XXXX} or {E:EID}

	Errors:
		IMI - invalid motor id
		IMD - invalid move direction
		ISV - invalid speed value

 READ - R:N
	where	R - command id
			N - motor id (0 - 6)

	errors:
		
 READ STATUS - RS
	
 ****************************************************/
void loop()
{
	byte buffer[4];

	// read positions

	// read serial
	if (Serial.available() > 0) {
		if (Serial.read() == '$') {
			// ready to receive command
			while (Serial.available() < 4) {
				;
			}
			Serial.readBytes(buffer, 4);
			RobotControl.processCommand(buffer);
		}
	}
}

void serialEvent()
{
	while (Serial.available()) {
		char ch = Serial.read();
		if (ch == '{') // this is the beginning of command
		{
			// start command buffering
			Requ
		}
	}
}

void setError()
{

}
