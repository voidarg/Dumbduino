// 
// 
// 
#include "RequestReader.h"
#include "Diagnostics.h"

RequestReaderClass RequestReader;


RequestReaderClass::RequestReaderClass()
{
	parameterBuffer.reserve(MaxParameterLength);
	reset();
}

void RequestReaderClass::reset() {
	packetStatus = WaitingForStartTag;
	readStatus = Noop;
	parameterBuffer = "";
}

RequestReaderClass::PacketStatus RequestReaderClass::getPacketStatus() {
	return packetStatus;
}

RequestReaderClass::ReadStatus RequestReaderClass::getReadStatus() {
	return readStatus;
}

bool RequestReaderClass::getCommand(char &command) {
	if (readStatus == ReadStatus::CommandAvailable) {
		command = parameterBuffer[0];
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getStringParam(String &s) {
	if (readStatus == ReadStatus::ParamAvailable) {
		s = parameterBuffer;
		parameterBuffer = "";
		readStatus = ReadStatus::Receiving;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getCharParam(char &ch) {
	if (readStatus == ReadStatus::ParamAvailable) {
		ch = parameterBuffer[0];
		parameterBuffer = "";
		readStatus = ReadStatus::Receiving;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getIntParam(int& iparam) {
	if (readStatus == ReadStatus::ParamAvailable) {
		iparam = parameterBuffer.toInt();
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getFloatParam(float& fparam) {
	if (readStatus == ReadStatus::ParamAvailable) {
		fparam = parameterBuffer.toFloat();
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getDoubleParam(double& dparam) {
	if (readStatus == ReadStatus::ParamAvailable) {
		dparam = parameterBuffer.toDouble();
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getLongParam(long& lparam) {
	if (readStatus == ReadStatus::ParamAvailable) {
		lparam = parameterBuffer.toInt();
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

bool RequestReaderClass::getByteParam(byte& param) {
	if (readStatus == ReadStatus::ParamAvailable) {
		param = parameterBuffer.toInt();
		parameterBuffer = "";
		readStatus = ReadStatus::Noop;
		return true;
	}
	else {
		return false;
	}
}

RequestReaderClass::ReadStatus RequestReaderClass::readNext() {
	
	ReadStatus rs;
	do {
		rs = readPacketChar();
	} while (rs == ReadStatus::Receiving);
	
	return rs;
}

RequestReaderClass::ReadStatus RequestReaderClass::readPacketChar() {
	if (Serial.available() == 0) {
		Result.set(ResultClass::Waiting);
		readStatus = ReadStatus::WaitingForData;	// will allow to control time outs
		return readStatus;
	}

	char ch = Serial.peek();
	switch (ch) {
		case RequestReaderClass::StartChar:
		{
			if (packetStatus == PacketStatus::WaitingForStartTag) {
				(void)Serial.read();
				Result.set (ResultClass::Pending);
				packetStatus = PacketStatus::WaitingForCommandByte;
				readStatus = ReadStatus::Receiving;
			}
			else {
				Result.set(ResultClass::CorruptPacket);
				packetStatus = PacketStatus::WaitingForStartTag;
				readStatus = ReadStatus::Error;
			}
			break;
		}
		case RequestReaderClass::EndChar:
		{
			if (packetStatus == PacketStatus::WaitingForParamOrEof) {
				if (parameterBuffer.length() > 0) {
					Result.set(ResultClass::Success);
					readStatus = ReadStatus::ParamAvailable;
					// packetStatus will remain the same and the eof character will be read and
					// dismissed on the next read
				}
				else {
					(void)Serial.read();			// clear character out of the buffer
					Result.set(ResultClass::Pending);
					packetStatus = PacketStatus::WaitingForStartTag;
					readStatus = ReadStatus::Eof;	// set eof
				}
			}
			else if (packetStatus == PacketStatus::WaitingForCommandByte) {
				(void)Serial.read();
				Result.set(ResultClass::CorruptPacket);
				packetStatus = WaitingForStartTag;
				readStatus = ReadStatus::Error;
			}
			else { // waiting for the packet start, ignore garbage, but report, that the data is being transmitted
				(void) Serial.read();
				readStatus = ReadStatus::Receiving;
				Result.set(ResultClass::Pending);
			}
			break;
		}
		case RequestReaderClass::ArgumentDelimiter:
		{
			if (packetStatus = PacketStatus::WaitingForParamOrEof) {
				// we have received a parameter
				(void)Serial.read();
				Result.set(ResultClass::Success);
				// packetStatus will be unchanged
				readStatus = ReadStatus::ParamAvailable;
			}
			else if (packetStatus == PacketStatus::WaitingForCommandByte) {
				// this is an error
				(void)Serial.read();	// read the character from the buffer
				Result.set(ResultClass::CorruptPacket);
				packetStatus = PacketStatus::WaitingForStartTag;	// reset the packet status to wait for the next valid packet
				readStatus = ReadStatus::Error;
			}
			else { // waiting for the packet start
				(void)Serial.read();
				Result.set(ResultClass::Pending);
				readStatus = ReadStatus::Receiving;
			}
			break;
		}
		default:	// reading packet data
		{
			if (packetStatus == PacketStatus::WaitingForCommandByte) {
				// we have received a command byte
				parameterBuffer = (char)Serial.read();
				Result.set(ResultClass::Pending);
				packetStatus = PacketStatus::WaitingForParamOrEof;
				readStatus = ReadStatus::CommandAvailable;
			}
			else {
				if (parameterBuffer.length() >= MaxParameterLength) {
					(void)Serial.read();
					Result.set(ResultClass::ParameterIsTooLong);
					readStatus = ReadStatus::Error;
					packetStatus = PacketStatus::WaitingForStartTag;
				}
				else {
					parameterBuffer += (char)Serial.read();
					Result.set(ResultClass::Pending);
					readStatus = ReadStatus::Receiving;
				}
			}
		}
	}
	return readStatus;
}
