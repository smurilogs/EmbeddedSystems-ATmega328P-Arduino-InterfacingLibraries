
#include "HMC5883L.h"

HMC5883L::HMC5883L()
{

}

void HMC5883L::init()
{
    // Keeps Typical Data Output Rate in 15Hz, and keeps default axis orientation
    TWI::writeRegister(HMC5883L_ADDRESS, HMC5883L_CONF_A, 0b00010000);

    // Keeps Digital Resolution of 0.92mGa/LSb (recommedend field range = ±1.3Ga)
    TWI::writeRegister(HMC5883L_ADDRESS, HMC5883L_CONF_B, 0b00100000);

    // Sets Continuous-Measurement Mode
    TWI::writeRegister(HMC5883L_ADDRESS, HMC5883L_MODSEL, 0b000000000);
}

uint16_t HMC5883L::getXMagne()
{
  // If bit RDY is zero then wait until it's set, indicating that data is ready
  uint8_t STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);
  while(!(STATUSREG & (1 << 0)))
    STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);

  TWI::start(TWI::addW(HMC5883L_ADDRESS));
  TWI::write(0x03);                // register to read

  TWI::start(TWI::addR(HMC5883L_ADDRESS));
  uint8_t xMSB = TWI::readACK();
  uint8_t xLSB = TWI::readACK();
  uint8_t zMSB = TWI::readACK();
  uint8_t zLSB = TWI::readACK();
  uint8_t yMSB = TWI::readACK();
  uint8_t yLSB = TWI::readACK();
  TWI::stop();

  uint16_t x = ((xMSB << 8) | xLSB);
  return x;
}

uint16_t HMC5883L::getYMagne()
{
  // If bit RDY is zero then wait until it's set, indicating that data is ready
  uint8_t STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);
  while(!(STATUSREG & (1 << 0)))
    STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);

  TWI::start(TWI::addW(HMC5883L_ADDRESS));
  TWI::write(0x03);                // register to read

  TWI::start(TWI::addR(HMC5883L_ADDRESS));
  uint8_t xMSB = TWI::readACK();
  uint8_t xLSB = TWI::readACK();
  uint8_t zMSB = TWI::readACK();
  uint8_t zLSB = TWI::readACK();
  uint8_t yMSB = TWI::readACK();
  uint8_t yLSB = TWI::readACK();
  TWI::stop();

  uint16_t y = ((yMSB << 8) | yLSB);
  return y;
}

uint16_t HMC5883L::getZMagne()
{
  // If bit RDY is zero then wait until it's set, indicating that data is ready
  uint8_t STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);
  while(!(STATUSREG & (1 << 0)))
    STATUSREG = TWI::readRegister(HMC5883L_ADDRESS, HMC5883L_STATUS);

  TWI::start(TWI::addW(HMC5883L_ADDRESS));
  TWI::write(0x03);                // register to read

  TWI::start(TWI::addR(HMC5883L_ADDRESS));
  uint8_t xMSB = TWI::readACK();
  uint8_t xLSB = TWI::readACK();
  uint8_t zMSB = TWI::readACK();
  uint8_t zLSB = TWI::readACK();
  uint8_t yMSB = TWI::readACK();
  uint8_t yLSB = TWI::readACK();
  TWI::stop();

  uint16_t z = ((yMSB << 8) | zLSB);
  return z;
}
