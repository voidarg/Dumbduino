// ErrorCodes.h

#ifndef _ERRORCODES_h
#define _ERRORCODES_h

namespace Result
{
	enum ResultCode
	{
		Waiting = -2,			// request in progress. waiting for data
		Pending = -1,			// this is not an error. it indicates, that called handler does not process this command
		Success = 0,			// success
		UnrecognizedCommand,	
		CorruptPacket,
		RxTimeout,
		ParameterOutOfRange,
	};
}

#endif

