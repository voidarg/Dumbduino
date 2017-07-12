// ErrorCodes.h

#ifndef _ERRORCODES_h
#define _ERRORCODES_h

struct ResultClass
{
public:
	enum ResultCode
	{
		EOP = -3,				// end of packet
		Waiting = -2,			// request in progress. waiting for data
		Pending = -1,			// this is not an error. it indicates, that called handler does not process this command
		Success = 0,			// success
		UnrecognizedCommand,	
		CorruptPacket,
		RxTimeout,
		ParameterOutOfRange,
		ParameterIsTooLong
	};

	ResultClass() {
		reset();
	}

	inline void set(ResultCode r) {
		result = r;
	}
	
	inline ResultCode get() const {
		return result;
	}

	inline void reset() {
		result = Success;
	}

	inline bool Succeeded() const {
		return Succeeded (result);
	}

	inline bool Failed() const {
		return Failed (result);
	}

	inline bool Ready() const {
		return Ready(result);
	}

	inline static bool Succeeded(ResultClass::ResultCode r) {
		return r == Success;
	}

	inline static bool Failed(ResultClass::ResultCode r) {
		return r > Success;
	}

	inline static bool Ready(ResultClass::ResultCode r) {
		return r >= Success;
	}

	inline operator ResultCode() const {
		return get();
	}

private:
	ResultCode result;
};

extern ResultClass Result;
#endif

