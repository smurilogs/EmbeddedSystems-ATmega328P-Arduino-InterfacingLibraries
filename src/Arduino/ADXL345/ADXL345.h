
#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include <Wire.h>

#define CTRL_REGID 0
#define CTRL_REG2D 0x2D
#define CTRL_REGX0 0x32
#define CTRL_REGX1 0x33
#define CTRL_REGY0 0x34
#define CTRL_REGY1 0x35
#define CTRL_REGZ0 0x36
#define CTRL_REGZ1 0x37
#define ADXL345_ADDRESS 0x53

class ADXL345
{
public:
    ADXL345();
    void begin();

    uint16_t getXAccel();
    uint16_t getYAccel();
    uint16_t getZAccel();

private:
    void writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val);
    uint8_t readRegister(uint8_t deviceAddress, uint8_t address);
};

#endif