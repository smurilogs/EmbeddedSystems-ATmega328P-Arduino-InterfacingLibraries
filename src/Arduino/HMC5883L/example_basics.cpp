
#include <Arduino.h>
#include "HMC5883L.h"

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
    int x = magne.getXMagne();
    Serial.println(x);

    int y = magne.getYMagne();
    Serial.println(y);

    int z = magne.getZMagne();
    Serial.println(z);

    Serial.println();
    delay(100); 
}