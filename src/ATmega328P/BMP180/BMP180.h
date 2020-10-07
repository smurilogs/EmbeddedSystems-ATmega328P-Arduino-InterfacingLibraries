
#ifndef BMP180_H
#define BMP180_H

#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include "I2C.h"

#define BMP180_ADDRESS 0x77
#define CTRL_MEAS 0xF4
#define BMP180_OUT_MSB 0xF6
#define BMP180_OUT_LSB 0xF7
#define BMP180_OUT_XLSB 0xF8

class BMP180
{
private:
    // Oversampling setting
    static uint8_t OSS;

    // Calibration variables
    static int16_t b1, b2, ac1, ac2, ac3, mb, mc, md;
    static uint16_t ac4, ac5, ac6;

    // Calc variables
    static int32_t x1, x2, x3, UT, UP, T, P, b3, b5, b6;
    static uint32_t b4, b7;

public:
    BMP180();
    static void init();
    static void getUT1(void);
    static void getUT2(void);
    static int32_t getT(void);
    static void getUP1(void);
    static void getUP2(void);
    static int32_t getP(void);
};

#endif
