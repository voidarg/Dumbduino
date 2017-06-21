
#include "RobotControl.h"
#include "Config.h"

void setup()
{
	/* add setup code here */
	RobotControl.init();
	Serial.begin(115200);
}

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
