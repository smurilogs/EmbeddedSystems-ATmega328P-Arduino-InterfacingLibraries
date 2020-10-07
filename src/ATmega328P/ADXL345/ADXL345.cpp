
#include "ADXL345.h"

ADXL345::ADXL345()
{

}

void ADXL345::init()
{
    // Sets g-range to ±16g and keeps full resolution output
    //TWIwriteRegister(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, 0b00001011);

    // Sets g-range to ±4g and keeps 10-bit resolution output
    TWI::writeRegister(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, 0b00000001);

    // Sets g-range to ±16g and keeps 10-bit resolution output
    //TWI::writeRegister(ADXL345_ADDRESS, ADXL345_DATA_FORMAT, 0b00000011);


    // Sets measurement mode
    TWI::writeRegister(ADXL345_ADDRESS, ADXL345_POWER_CTL, 0b00001000);
}

uint16_t ADXL345::getXAccel()
{
    uint8_t xLSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAX0);
    uint8_t xMSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAX1);
    uint16_t x = ((xMSB << 8) | xLSB);
    return x;
}

uint16_t ADXL345::getYAccel()
{
    uint8_t yLSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAY0);
    uint8_t yMSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAY1);
    uint16_t y = ((yMSB << 8) | yLSB);
    return y;
}

uint16_t ADXL345::getZAccel()
{
    uint8_t zLSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAZ0);
    uint8_t zMSB = TWI::readRegister(ADXL345_ADDRESS, ADXL345_DATAZ1);
    uint16_t z = ((zMSB << 8) | zLSB);
    return z;
}
