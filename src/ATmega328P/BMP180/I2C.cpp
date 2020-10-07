
#include "I2C.h"

I2C::I2C(void)
{

}


void I2C::init(void)
{
    // 400kHz of SCL from 16MHz of fSYS
    TWSR &= ~(1 << 1) & ~(1 << 0);         // Sets prescaler as 1
    TWBR = 12;                             // Calc reference value for SCL

    //(IF YOU'RE GONNA USE INTERRUPT)
    //TWCR != (1 << 0);     // Enables the I2C module interrupt

    // Enables I2C module
    TWCR |= (1 << 2);
}

void I2C::initAsSlave(void)
{
    // to do
}

uint8_t I2C::start(uint8_t aDevAddr)
{
    // reset I2C control register
    TWCR = 0;

    // transmit START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // check if the start condition was successfully transmitted
    if((TWSR & 0xF8) != TW_START){ return 1; }

    // load slave address into data register
    TWDR = aDevAddr;

    // start transmission of address
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)) );

    // check if the device has acknowledged the READ / WRITE mode
    uint8_t twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
        return 1;

    return 0;
}

uint8_t I2C::write(uint8_t aData)
{
    // load data into data register
    TWDR = aData;

    // start transmission of data
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)));

    if((TWSR & 0xF8) != TW_MT_DATA_ACK )
        return 1;

    return 0;
}

uint8_t I2C::readACK(void)
{
    // start I2C module and acknowledge data after reception
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // return received data from TWDR
    return TWDR;
}

uint8_t I2C::readNACK(void)
{
    // start receiving without acknowledging reception
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // return received data from TWDR
    return TWDR;
}

void I2C::stop(void)
{
    // transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


uint8_t I2C::addW(uint8_t aDevAddr)
{
    uint8_t data;
    data |= (aDevAddr << 1) | (0 << 0);

    return data;
}

uint8_t I2C::addR(uint8_t aAddr)
{
    uint8_t data;
    data |= (aAddr << 1) | (1 << 0);

    return data;
}

void I2C::writeRegister8(uint8_t aDevAddr, uint8_t aRegAddr, uint8_t aData)
{
    I2C::start(I2C::addW(aDevAddr));       // start transmission to device
    I2C::write(aRegAddr);                // send register address
    I2C::write(aData);                   // send value to write
    I2C::stop();                         // end transmission
}

uint8_t I2C::readRegister8(uint8_t aDevAddr, uint8_t aRegAddr)
{
    uint8_t b1;

    I2C::start(I2C::addW(aDevAddr));
    I2C::write(aRegAddr);                // register to read
    //I2C::stop();

    I2C::start(I2C::addR(aDevAddr));
    b1 = I2C::readNACK();
    I2C::stop();

    return b1;
}

uint16_t I2C::readRegister16(uint8_t aDevAddr, uint8_t aRegAddr)
{
    uint16_t b1, b2;
    uint16_t r;

    I2C::start(I2C::addW(aDevAddr));
    I2C::write(aRegAddr);                // register to read
    //I2C::stop();

    I2C::start(I2C::addR(aDevAddr));
    b1 = I2C::readACK();
    b2 = I2C::readNACK();
    I2C::stop();

    r = (b1 << 8) | b2;

    return r;
}
