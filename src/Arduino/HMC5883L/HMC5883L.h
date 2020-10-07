 
#ifndef HMC5883L_H
#define HMC5883L_H

#include <stdint.h>
#include <Wire.h>

#define CTRL_REGMODSEL 0x02
#define CONFIG_CONTMOD 0x00

#define CTRL_REGXMSB 0x03
#define CTRL_REGXLSB 0x04
#define CTRL_REGYMSB 0x07
#define CTRL_REGYLSB 0x08
#define CTRL_REGZMSB 0x05
#define CTRL_REGZLSB 0x06
#define HMC5883L_ADDRESS 0x1E

class HMC5883L
{
public:
	HMC5883L();
	void begin();

	uint16_t getXMagne();
	uint16_t getYMagne();
	uint16_t getZMagne();

private:
	void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
	uint8_t readRegister(uint8_t deviceAddress, uint8_t address);
};

 #endif