// RequestFormat.h

#ifndef _REQUESTFORMAT_h
#define _REQUESTFORMAT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ErrorCodes.h"


struct RequestReaderClass
{
public:
	const static char StartChar = '{';
	const static char EndChar = '}';
	const static char ArgumentDelimiter = ',';
	const static int MaxParameterLength = 15;

	enum PacketStatus {
		WaitingForStartTag,
		WaitingForCommandByte,
		WaitingForParamOrEof
	};

	enum ReadStatus {
		Error = -1,
		Noop,
		Receiving,
		WaitingForData,
		CommandAvailable,
		ParamAvailable,
		Eof
	};

public:
	RequestReaderClass();
	ReadStatus readNext();
	ReadStatus readPacketChar();

	void reset();
	PacketStatus getPacketStatus();
	ReadStatus getReadStatus();
	ResultClass::ResultCode getErrorCode();

	bool getCommand(char &command);
	bool getStringParam(String &s);
	bool getCharParam(char &ch);
	bool getIntParam(int& iparam);
	bool getFloatParam(float& fparam);
	bool getDoubleParam(double& dparam);
	bool getLongParam(long& lparam);
	bool getByteParam(byte& param);

private:
	PacketStatus packetStatus;
	ReadStatus readStatus;
	String parameterBuffer;

private:
};

extern RequestReaderClass RequestReader;
#endif

