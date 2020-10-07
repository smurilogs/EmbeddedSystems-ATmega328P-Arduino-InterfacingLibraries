
#include "HMC5883L.h"

HMC5883L::HMC5883L()
{

}

void HMC5883L::begin()
{
	writeRegister(HMC5883L_ADDRESS, CTRL_REGMODSEL, CONFIG_CONTMOD);
}

uint16_t HMC5883L::getXMagne()
{
    uint8_t xLSB = readRegister(HMC5883L_ADDRESS, CTRL_REGXLSB);
    uint8_t xMSB = readRegister(HMC5883L_ADDRESS, CTRL_REGXMSB);
    uint16_t x = ((xMSB << 8) | xLSB);
    return x;
}

uint16_t HMC5883L::getYMagne()
{
    uint8_t yLSB = readRegister(HMC5883L_ADDRESS, CTRL_REGYLSB);
    uint8_t yMSB = readRegister(HMC5883L_ADDRESS, CTRL_REGYMSB);
    uint16_t y = ((yMSB << 8) | yLSB);
    return y;
}

uint16_t HMC5883L::getZMagne()
{
    uint8_t zLSB = readRegister(HMC5883L_ADDRESS, CTRL_REGZLSB);
    uint8_t zMSB = readRegister(HMC5883L_ADDRESS, CTRL_REGZMSB);
    uint16_t z = ((zMSB << 8) | zLSB);
    return z;
}

void HMC5883L::writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val) 
{
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

uint8_t HMC5883L::readRegister(uint8_t deviceAddress, uint8_t address)
{
    uint8_t v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a uint8_t

    while(!Wire.available()) 
    {
        // waiting    Serial.println("flag2");
    }
    v = Wire.read();
    return v;
}