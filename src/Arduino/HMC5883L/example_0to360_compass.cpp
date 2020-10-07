
#include <Arduino.h>
#include <Math.h>
#include "HMC5883L.h"

#define OFFSETZ 0

HMC5883L magne;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    magne.begin();
    
    delay(1500); 
}

void loop()
{
    // Módulo travando quando não se faz essa sequencia de leitura
    float x = (int16_t) magne.getXMagne();
    float y = (int16_t) magne.getYMagne();
    float z = (int16_t) magne.getZMagne(); 

    float angRadZ = atan2(x, z);
    float angDegZ = angRadZ * (180.0/PI);

    // Scale transformation: [180, +180] to [0, +360[
    if(angDegZ > -180 && angDegZ < 0)
    {
        angDegZ = angDegZ * (-1);
        angDegZ = (180.0 - angDegZ);
        angDegZ = angDegZ + 180.0;
    }
    
    // Offset
    if((angDegZ + OFFSETZ) >= 360.0)
        angDegZ = (angDegZ + OFFSETZ) - 360.0;
    else
        angDegZ = angDegZ + OFFSETZ;


    Serial.println(angDegZ);
    Serial.println();
    delay(500); 
}