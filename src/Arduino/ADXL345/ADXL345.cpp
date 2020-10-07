
#include "ADXL345.h"

ADXL345::ADXL345()
{

}

void ADXL345::begin()
{
    writeRegister(ADXL345_ADDRESS, CTRL_REG2D, 8);
}

uint16_t ADXL345::getXAccel()
{
    uint8_t xLSB = readRegister(ADXL345_ADDRESS, CTRL_REGX0);
    uint8_t xMSB = readRegister(ADXL345_ADDRESS, CTRL_REGX1);
    uint16_t x = ((xMSB << 8) | xLSB);
    return x;
}

uint16_t ADXL345::getYAccel()
{
    uint8_t yLSB = readRegister(ADXL345_ADDRESS, CTRL_REGY0);
    uint8_t yMSB = readRegister(ADXL345_ADDRESS, CTRL_REGY1);
    uint16_t y = ((yMSB << 8) | yLSB);
    return y;
}

uint16_t ADXL345::getZAccel()
{
    uint8_t zLSB = readRegister(ADXL345_ADDRESS, CTRL_REGZ0);
    uint8_t zMSB = readRegister(ADXL345_ADDRESS, CTRL_REGZ1);
    uint16_t z = ((zMSB << 8) | zLSB);
    return z;
}

void ADXL345::writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val) 
{
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

uint8_t ADXL345::readRegister(uint8_t deviceAddress, uint8_t address)
{
    uint8_t v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a uint8_t

    while(!Wire.available()) 
    {
        // waiting
    }
    v = Wire.read();
    return v;
}