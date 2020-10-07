
#include "TWI.h"

TWI::TWI(void)
{

}


void TWI::initAsMaster(void)
{
    // 400kHz of SCL from 16MHz of fSYS
    TWSR &= ~(1 << 1) & ~(1 << 0);         // Sets prescaler as 1
    TWBR = 12;                             // Calc reference value for SCL

    //(IF YOU'RE GONNA USE INTERRUPT)
    //TWCR != (1 << 0);     // Enables the TWI module interrupt

    // Enables TWI module
    TWCR |= (1 << 2);
}

void TWI::initAsSlave(void)
{
    // to do
}

uint8_t TWI::start(uint8_t aDevAddr)
{
    // Resets TWI control register
    TWCR = 0;

    // Transmits START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Waits for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // Checks if the start condition was successfully transmitted
    if((TWSR & 0xF8) != TW_START){ return 1; }

    // Loads slave address into data register
    TWDR = aDevAddr;

    // Starts transmission of address
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Waits for end of transmission
    while(!(TWCR & (1 << TWINT)) );

    // Checks if the device has acknowledged the READ / WRITE mode
    uint8_t twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
        return 1;

    return 0;
}

uint8_t TWI::write(uint8_t aData)
{
    // Loads data into data register
    TWDR = aData;

    // Starts transmission of data
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Waits for end of transmission
    while(!(TWCR & (1 << TWINT)));

    if((TWSR & 0xF8) != TW_MT_DATA_ACK )
        return 1;

    return 0;
}

uint8_t TWI::readACK(void)
{
    // Starts TWI module and acknowledge data after reception
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    // Waits for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // Returns received data from TWDR
    return TWDR;
}

uint8_t TWI::readNACK(void)
{
    // start receiving without acknowledging reception
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wait for end of transmission
    while(!(TWCR & (1 << TWINT)));

    // return received data from TWDR
    return TWDR;
}

void TWI::stop(void)
{
    // transmit STOP condition
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}


uint8_t TWI::addW(uint8_t aDevAddr)
{
    uint8_t data;

    // Concatenates a 0 in the end of a given 7-bit address 
    data |= (aDevAddr << 1) | (0 << 0);

    return data;
}

uint8_t TWI::addR(uint8_t aDevAddr)
{
    uint8_t data;

    // Concatenates a 1 in the end of a given 7-bit address
    data |= (aDevAddr << 1) | (1 << 0);

    return data;
}

void TWI::writeRegister(uint8_t aDevAddr, uint8_t aRegAddr, uint8_t aData)
{
    TWI::start(TWI::addW(aDevAddr));     // Starts transmission to device
    TWI::write(aRegAddr);                // Sends register address
    TWI::write(aData);                   // Sends value to write
    TWI::stop();                         // Ends transmission
}

uint8_t TWI::readRegister(uint8_t aDevAddr, uint8_t aRegAddr)
{
    uint8_t data;

    TWI::start(TWI::addW(aDevAddr));
    TWI::write(aRegAddr);                // register to read

    TWI::start(TWI::addR(aDevAddr));
    data = TWI::readNACK();
    TWI::stop();

    return data;
}
