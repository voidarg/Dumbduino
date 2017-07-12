// 
// 
//
#include "Diagnostics.h"
#include "ErrorCodes.h"
#include "RequestReader.h"
#include "Request.h"
#include "Diagnostics.h"


void RequestClass::init()
{
	current = NULL;
	reset();
}

void RequestClass::reset()
{
	if (current) {
		current->clear();
		current = NULL;
	}

	receiving = false;
	status = ResultClass::Waiting;
}

ResultClass::ResultCode RequestClass::processNext()
{
	RequestReaderClass::ReadStatus rs = RequestReader.readNext();
	switch (rs)
	{
		case RequestReaderClass::ReadStatus::WaitingForData:
			break; // TODO: timeout tracking
		case RequestReaderClass::ReadStatus::CommandAvailable:
		{	
			// get command here
			char command;
			if (RequestReader.getCommand(command)) {
				selectInterface(command);
			}
			else {
				RequestReader.reset();
			}
			break;
		}
		case RequestReaderClass::ReadStatus::ParamAvailable:
			if (ResultClass::Succeeded(current->process())) {
				Result.set(ResultClass::Pending);
			}
			break;
		case RequestReaderClass::ReadStatus::Eof:
			Result.set(ResultClass::Success);
			RequestReader.reset();
			break;
		case RequestReaderClass::ReadStatus::Error:
			RequestReader.reset();
			break;
		default:
		{
			Result.set(ResultClass::ResultCode::Pending);
		}
	}
	return Result;
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
		status = ResultClass::UnrecognizedCommand;
	}
}

RequestClass Request;
