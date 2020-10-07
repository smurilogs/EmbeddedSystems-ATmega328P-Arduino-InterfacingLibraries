
#ifndef HMC5883L_H
#define HMC5883L_H

#include <stdint.h>
#include "TWI.h"

#define HMC5883L_CONF_A 0x00
#define HMC5883L_CONF_B 0x01
#define HMC5883L_MODSEL 0x02
#define HMC5883L_STATUS 0x09

#define HMC5883L_DATAOUT_XMSB 0x03
#define HMC5883L_DATAOUT_XLSB 0x04
#define HMC5883L_DATAOUT_YMSB 0x07
#define HMC5883L_DATAOUT_YLSB 0x08
#define HMC5883L_DATAOUT_ZMSB 0x05
#define HMC5883L_DATAOUT_ZLSB 0x06

#define HMC5883L_ADDRESS 0x1E

class HMC5883L
{
public:
	HMC5883L();
	void init();
	uint16_t getXMagne();
	uint16_t getYMagne();
	uint16_t getZMagne();
};

 #endif
