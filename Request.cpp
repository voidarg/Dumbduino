// 
// 
// 
#include "ErrorCodes.h"
#include "RequestFormat.h"
#include "Request.h"

void RequestClass::init()
{
	clear();
}

void RequestClass::clear()
{
	receiving = false;
	current = NULL;
	status = Result::Waiting;
}

Result::ResultCode RequestClass::processNext()
{
	if (Serial.available()) {
		byte ch = Serial.peek();

    Serial.print ("*1");
		if (! receiving) {
      Serial.print ("*2");			
			
			if (ch == RequestFormat::StartChar) {
				Serial.print ("*3");
				receiving = true;
				status = Result::Pending;
			}
			(void) Serial.read(); // read the byte out of the buffer
		}
		else if (status == Result::Pending || status == Result::Waiting) {
			    Serial.print ("*4");
			
			// check if there is and unexpected start of the request
			if (ch == RequestFormat::StartChar) {
          Serial.print ("*5");
				status = Result::CorruptPacket;
			}
			else {
				// process input
            Serial.print ("*6");
				ch = Serial.read();
				if (current == NULL) {	// we don't have command byte yet, then this is it
					    Serial.print ("*7");
					selectInterface(ch);

					if (current != NULL) {	// if appropriate interface was located
						    Serial.print ("*8");
						status = current->process();
					}
				}
				else {
              Serial.print ("*9");
					status = current->process();
				}
			}
		}
	}
	else {
		status = Result::Waiting;
	}
	return status;
}


void RequestClass::selectInterface(char id)
{
	switch (id)
	{
	case MoveRequest_M::RequestId:
    Serial.print ("*SI1");
		current = (MoveRequest_M*)this;
		break;

	case PositionRequest_P::RequestId:
  Serial.print ("*SI2");
		current = (PositionRequest_P*)this;
		break;

	default: // invalid command id
    Serial.print ("*SI3");
		status = Result::UnrecognizedCommand;
	}
}

RequestClass Request;
