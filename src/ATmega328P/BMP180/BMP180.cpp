
#include "BMP180.h"

uint8_t BMP180::OSS = 0;

int16_t BMP180::ac1 = 0;
int16_t BMP180::ac2 = 0;
int16_t BMP180::ac3 = 0;
int16_t BMP180::b1 = 0;
int16_t BMP180::b2 = 0;
int16_t BMP180::mb = 0;
int16_t BMP180::mc = 0;
int16_t BMP180::md = 0;

uint16_t BMP180::ac4 = 0;
uint16_t BMP180::ac5 = 0;
uint16_t BMP180::ac6 = 0;

int32_t BMP180::x1 = 0;
int32_t BMP180::x2 = 0;
int32_t BMP180::x3 = 0;
int32_t BMP180::UT = 0;
int32_t BMP180::UP = 0;
int32_t BMP180::T = 0;
int32_t BMP180::P = 0;
int32_t BMP180::b3 = 0;
int32_t BMP180::b5 = 0;
int32_t BMP180::b6 = 0;

uint32_t BMP180::b4 = 0;
uint32_t BMP180::b7 = 0;

BMP180::BMP180()
{

}

void BMP180::init(void)
{
    OSS = 3;

    // Gets calibration variables, see datasheet
    ac1 = I2C::readRegister16(BMP180_ADDRESS, 0xAA);
    ac2 = I2C::readRegister16(BMP180_ADDRESS, 0xAC);
    ac3 = I2C::readRegister16(BMP180_ADDRESS, 0xAE);
    ac4 = I2C::readRegister16(BMP180_ADDRESS, 0xB0);
    ac5 = I2C::readRegister16(BMP180_ADDRESS, 0xB2);
    ac6 = I2C::readRegister16(BMP180_ADDRESS, 0xB4);
    b1 = I2C::readRegister16(BMP180_ADDRESS, 0xB6);
    b2 = I2C::readRegister16(BMP180_ADDRESS, 0xB8);
    mb = I2C::readRegister16(BMP180_ADDRESS, 0xBA);
    mc = I2C::readRegister16(BMP180_ADDRESS, 0xBC);
    md = I2C::readRegister16(BMP180_ADDRESS, 0xBE);
}

void BMP180::getUT1(void)
{
    I2C::writeRegister8(BMP180_ADDRESS, CTRL_MEAS, 0x2E);
    // wait 3.4ms
}

void BMP180::getUT2(void)
{
    // Gets uncompensated temperature
    int32_t tMSB = I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_MSB);
    int32_t tLSB = I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_LSB);
    UT = (tMSB << 8) | tLSB;

    //UT = I2C::readRegister16(BMP180_ADDRESS, BMP180_OUT_MSB);
}

int32_t BMP180::getT(void)
{
    // Calcs true temperature
    x1 = (UT - (int32_t)ac6) * ((int32_t)ac5) >> 15;
    x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
    b5 = x1 + x2;
    T = (b5 + 8) >> 4;

    return T;
}

void BMP180::getUP1(void)
{
    I2C::writeRegister8(BMP180_ADDRESS, CTRL_MEAS, (0x34 + (OSS << 6)));
    // wait 3.4ms
}

void BMP180::getUP2(void)
{
    // Gets uncompensated Pressure
    //int32_t pMSB = I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_MSB);
    //int32_t pLSB = I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_LSB);
    //int32_t pXLSB = I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_XLSB);
    UP = I2C::readRegister16(BMP180_ADDRESS, BMP180_OUT_MSB);
    UP = UP << 8;
    UP = UP | I2C::readRegister8(BMP180_ADDRESS, BMP180_OUT_XLSB);
    UP = UP >> (8 - OSS);
    //UP = (temp >> (8 - OSS));

    //UP = ((pMSB << 16) | (pLSB << 8) | pXLSB) >> (8 - OSS);
}

int32_t BMP180::getP(void)
{
    b6 = b5 - 4000;
    x1 = ((int32_t)b2 * ( (b6 * b6) >>12 )) >> 11;
    x2 = ((int32_t)ac2 * b6) >> 11;
    x3 = x1 + x2;
    b3 = ((((int32_t)ac1*4 + x3) << OSS) + 2) / 4;
    x1 = ((int32_t)ac3 * b6) >> 13;
    x2 = ((int32_t)b1 * ((b6 * b6) >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = ((uint32_t)ac4 * (uint32_t)(x3 + 32768)) >> 15;
    b7 = ((uint32_t)UP - b3) * (uint32_t)( 50000UL >> OSS);
    if (b7 < 0x80000000) {
      P = (b7 * 2) / b4;
    } else {
      P = (b7 / b4) * 2;
    }
    x1 = (P >> 8) * (P >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * P) >> 16;
    P = P + ((x1 + x2 + (int32_t)3791) >> 4);

    return P;
}
