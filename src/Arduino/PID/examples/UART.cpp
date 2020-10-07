#include "UART.h"

UART::UART(void)
{

}

void UART::init(uint16_t _baudrate)
{
    uint16_t MYUBRR = F_CPU/16/_baudrate - 1;

    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;

    UCSR0B |= (1 << 4) | (1 << 3);   // Enables receiver and transmitter
    UCSR0C |= (1 << 2) | (1 << 1);   // Sets 8-bit data transmission
    UCSR0C &= ~(1 << 5) & ~(1 << 4); // Sets no parity
    UCSR0C &= ~(1 << 3);             // Sets 1 stop bit

    //(IF YOU'RE GONNA USE INTERRUPTS - don't forget sei();)
    UCSR0B |= (1 << 7);                 // Enables interrupt for a RX event
    //UCSR0B |= (1 << 6);                 // Enables interrupt for a TX event
    //UCSR0B |= (1 << 5);                 // Enables interrupt for a DRE event
}

bool UART::isDataAvailable(void)
{
    if(!(UCSR0A & (1 << RXC0)))
        return true;
    else
        return false;
}

uint8_t UART::readByte(void)
{
    while(!(UCSR0A & (1 << RXC0)));  // Waits until a data is available
    return UDR0;                     // Now UART has data from host in its buffer
}

void UART::readString(uint8_t *aString, uint32_t aLength)
{
    uint32_t i;

    for(i = 0; i < aLength; i++)
        aString[i] = UART::readByte();

    aString[i] = '\0';
}

void UART::writeByte(uint8_t aData)
{
    while(!(UCSR0A & (1 << UDRE0)));  // Waits until the transmitter is ready to send data
        UDR0 = aData;                 // Writes the data to UART buffer to be sent
}

void UART::writeString(uint8_t *aString)
{
    uint32_t i;

    for(i = 0; aString[i] != '\0'; i++)
        UART::writeByte(aString[i]);
}
