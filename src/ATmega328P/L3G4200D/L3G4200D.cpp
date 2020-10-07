
#include "L3G4200D.h"

L3G4200D::L3G4200D()
{

}

void L3G4200D::init()
{
    // Enable x, y, z and turn off power down:
    TWI::writeRegister(L3G4200D_ADDRESS, CTRL_REG1, 0b00001111);

    // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
    TWI::writeRegister(L3G4200D_ADDRESS, CTRL_REG2, 0b00000000);

    // Configure CTRL_REG3 to generate data ready interrupt on INT2
    // No interrupts used on INT1, if you'd like to configure INT1
    // or INT2 otherwise, consult the datasheet:
    TWI::writeRegister(L3G4200D_ADDRESS, CTRL_REG3, 0b00001000);


    // Sets sensitivity of 520dps (degrees per second)
    // TWIwriteRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00000000);

    // Sets sensitivity of 500dps (degrees per second)
    // TWIwriteRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00010000);

    // Sets sensitivity of 2000dps (degrees per second)
    TWI::writeRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00110000);

    // CTRL_REG5 controls high-pass filtering of outputs, use it if you'd like:
    TWI::writeRegister(L3G4200D_ADDRESS, CTRL_REG5, 0b00000000);
}

uint16_t L3G4200D::getXGyro()
{
    uint8_t xMSB = TWI::readRegister(L3G4200D_ADDRESS, 0x29);
    uint8_t xLSB = TWI::readRegister(L3G4200D_ADDRESS, 0x28);
    uint16_t x = ((xMSB << 8) | xLSB);
    return x;
}

uint16_t L3G4200D::getYGyro()
{
    uint8_t yMSB = TWI::readRegister(L3G4200D_ADDRESS, 0x2B);
    uint8_t yLSB = TWI::readRegister(L3G4200D_ADDRESS, 0x2A);
    uint16_t y = ((yMSB << 8) | yLSB);
    return y;
}

uint16_t L3G4200D::getZGyro()
{
  uint8_t zMSB = TWI::readRegister(L3G4200D_ADDRESS, 0x2D);
  uint8_t zLSB = TWI::readRegister(L3G4200D_ADDRESS, 0x2C);
  uint16_t z = ((zMSB << 8) | zLSB);
  return z;
}
