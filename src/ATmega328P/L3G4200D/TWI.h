
#ifndef TWI_h
#define TWI_h

#include <avr/interrupt.h>
#include <util/twi.h>

class TWI
{
public:
	TWI();
	static void initAsMaster(void);
	static void initAsSlave(void);
	static void writeRegister(uint8_t aDevAddr, uint8_t aRegAddr, uint8_t aData);
	static uint8_t readRegister(uint8_t aDevAddr, uint8_t aRegAddr);
	
	static uint8_t start(uint8_t aDevAddr);
	static uint8_t write(uint8_t aData);
	static uint8_t readACK(void);
	static uint8_t readNACK(void);
	static void stop(void);
	static uint8_t addW(uint8_t aDevAddr);
	static uint8_t addR(uint8_t aAddr);
};

#endif
