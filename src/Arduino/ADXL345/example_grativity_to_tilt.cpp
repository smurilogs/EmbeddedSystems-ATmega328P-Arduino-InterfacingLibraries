
#include <Arduino.h>
#include <stdint.h>
#include <Math.h>
#include "ADXL345.h"

#define OFFSETX 270
#define OFFSETY 270

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
    // Data acquisition from accelerometer
    float x = (int16_t) accel.getXAccel();
    float y = (int16_t) accel.getYAccel();
    float z = (int16_t) accel.getZAccel();

    // For around X axis...

    // Turning gravital vector components into angle in RAD
    float angRadX = atan2(z, y);
    // Turning angle in RAD into DEGREE
    float angDegX = angRadX * (180.0/PI);
    
    // Scale transformation: [-180, +180] to [0, 360[
    if(angDegX > -180 && angDegX < 0)
    {
        angDegX = angDegX * (-1);
        angDegX = (180.0 - angDegX);
        angDegX = angDegX + 180.0;
    }
    
    // Offset
    if((angDegX + OFFSETX) >= 360.0)
        angDegX = (angDegX + OFFSETX) - 360.0;
    else
        angDegX = angDegX + OFFSETX;

    // For around Y axis...

    // Turning gravital vector components int angle in RAD
    float angRadY = atan2(z, x);
    // Turning angle in RAD into DEGREE
    float angDegY = angRadY * (180.0/PI);
    
    // Scale transformation: [-180, +180] to [0, 360[
    if(angDegY > -180 && angDegY < 0)
    {
        angDegY = angDegY * (-1);
        angDegY = (180.0 - angDegY);
        angDegY = angDegY + 180.0;
    }

    // Offset
    if((angDegY + OFFSETY) >= 360.0)
        angDegY = (angDegY + OFFSETY) - 360.0;
    else
        angDegY = angDegY + OFFSETY;

    // For presentation...

    Serial.println(angDegX);
    Serial.println(angDegY);
    Serial.println();
    delay(500); 
}