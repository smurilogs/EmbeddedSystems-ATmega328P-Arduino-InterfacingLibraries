
#ifndef L3G4200D_h
#define L3G4200D_h

#include <stdint.h>
#include "TWI.h"

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define L3G4200D_ADDRESS 52

class L3G4200D
{
public:
	L3G4200D();
	void init();
	uint16_t getXGyro();
	uint16_t getYGyro();
	uint16_t getZGyro();
};

#endif
