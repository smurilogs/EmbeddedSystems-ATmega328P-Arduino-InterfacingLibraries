#ifndef UART_h
#define UART_h

#include <avr/io.h>
#include <stdint.h>

class UART
{
public:
	UART();
	static void init(uint16_t _baudrate);
  	static bool isDataAvailable(void);
	static uint8_t readByte(void);
	static void readString(uint8_t *aString, uint32_t aLength);
	static void writeByte(uint8_t aData);
	static void writeString(uint8_t *aString);
};

#endif
