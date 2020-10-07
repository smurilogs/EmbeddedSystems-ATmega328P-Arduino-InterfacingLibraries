
#include <Arduino.h>
#include "L3G4200D.h"

L3G4200D gyro;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    gyro.begin();
    
    delay(1500); 
}

void loop()
{
    int x = gyro.getXGyro();
    Serial.println(x);

    int y = gyro.getYGyro();
    Serial.println(y);

    int z = gyro.getZGyro();
    Serial.println(z);

    Serial.println();
    delay(100); 
}