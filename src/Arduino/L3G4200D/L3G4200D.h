
#ifndef L3G4200D_H
#define L3G4200D_H

#include <stdint.h>
#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define L3G4200D_ADDRESS 105
#define L3G4200D_SCALE 2000

class L3G4200D
{
public:
    L3G4200D();
    void begin();
    
    uint16_t getXGyro();
    uint16_t getYGyro();
    uint16_t getZGyro();

private:
    void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
    uint8_t readRegister(uint8_t deviceAddress, uint8_t address);
};

#endif