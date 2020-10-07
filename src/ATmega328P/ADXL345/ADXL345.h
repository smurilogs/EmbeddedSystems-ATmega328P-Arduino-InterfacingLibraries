
#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include "TWI.h"

#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATA_FORMAT 0x31

#define ADXL345_DATAX0 0x32
#define ADXL345_DATAX1 0x33
#define ADXL345_DATAY0 0x34
#define ADXL345_DATAY1 0x35
#define ADXL345_DATAZ0 0x36
#define ADXL345_DATAZ1 0x37

#define ADXL345_ADDRESS 0x53

class ADXL345
{
public:
    ADXL345();
    void init();

    uint16_t getXAccel();
    uint16_t getYAccel();
    uint16_t getZAccel();
};

#endif