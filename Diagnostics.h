// Diagnostics.h

#ifndef _DIAGNOSTICS_h
#define _DIAGNOSTICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



template <typename T> 
void trace(const T& data) {
	Serial.print(data);
}

template <typename T>
void trace(const T* data) {
	Serial.print(data);
}

template <typename T>
void traceln(const T& data)  {
	Serial.println(data);
}

template <typename T>
void traceln(const T* data)  {
	Serial.println(data);
}
#endif

