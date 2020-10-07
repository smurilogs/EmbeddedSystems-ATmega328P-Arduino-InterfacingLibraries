
#ifndef I2C_h
#define I2C_h

#include <avr/interrupt.h>
#include <util/twi.h>

class I2C
{
public:
	I2C();
	static void init(void);
	static void initAsSlave(void);
	static void writeRegister8(uint8_t aDevAddr, uint8_t aRegAddr, uint8_t aData);
	static uint8_t readRegister8(uint8_t aDevAddr, uint8_t aRegAddr);
	static uint16_t readRegister16(uint8_t aDevAddr, uint8_t aRegAddr);

	static uint8_t start(uint8_t aDevAddr);
	static uint8_t write(uint8_t aData);
	static uint8_t readACK(void);
	static uint8_t readNACK(void);
	static void stop(void);
	static uint8_t addW(uint8_t aDevAddr);
	static uint8_t addR(uint8_t aAddr);
};

#endif
