
#include <Arduino.h>
#include <stdint.h>
#include <Math.h>
#include "ADXL345.h"

ADXL345 accel;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    accel.begin();
    
    delay(1500); 
}

void loop()
{
    float x = (int16_t) accel.getXAccel()* 0.00390625;
    Serial.println(x);

    float y = (int16_t) accel.getYAccel()* 0.00390625;
    Serial.println(y);

    float z = (int16_t) accel.getZAccel()* 0.00390625;
    Serial.println(z);

    Serial.println();
    delay(500); 
}