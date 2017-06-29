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
	bool receiving = false;
	current = NULL;
	status = Result::Waiting;
}

Result::ResultCode RequestClass::process()
{
	if (Serial.available()) {
		byte ch = Serial.peek();

		if (! receiving) {
			if (ch == RequestFormat::StartChar) {
				receiving = true;
				status = Result::Pending;
			}
			
			(void) Serial.read(); // read the byte out of the buffer
		}
		else if (status == Result::Pending || status == Result::Waiting) {
			// check if there is and unexpected start of the request
			if (ch == RequestFormat::StartChar) {
				status = Result::CorruptPacket;
			}
			else {
				// process input
				ch = Serial.read();
				if (current == NULL) {	// we don't have command byte yet, then this is it
					selectInterface(ch);

					if (current != NULL) {	// if appropriate interface was located
						status = current->process();
					}
				}
				else {
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
		current = (MoveRequest_M*)this;
		break;

	case PositionRequest_P::RequestId:
		current = (PositionRequest_P*)this;
		break;

	default: // invalid command id
		status = Result::UnrecognizedCommand;
	}
}

RequestClass Request;
