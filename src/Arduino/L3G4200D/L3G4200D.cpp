
#include "L3G4200D.h"

L3G4200D::L3G4200D()
{

}

void L3G4200D::begin()
{
      //From  Jim Lindblom of Sparkfun's code
    // Enable x, y, z and turn off power down:
    writeRegister(L3G4200D_ADDRESS, CTRL_REG1, 0b00001111);

    // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
    writeRegister(L3G4200D_ADDRESS, CTRL_REG2, 0b00000000);

    // Configure CTRL_REG3 to generate data ready interrupt on INT2
    // No interrupts used on INT1, if you'd like to configure INT1
    // or INT2 otherwise, consult the datasheet:
    writeRegister(L3G4200D_ADDRESS, CTRL_REG3, 0b00001000);
     
    // CTRL_REG4 controls the full-scale range, among other things:
    if(L3G4200D_SCALE == 250)
        writeRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00000000);
    else 
        if(L3G4200D_SCALE == 500)
            writeRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00010000);
        else
            writeRegister(L3G4200D_ADDRESS, CTRL_REG4, 0b00110000);

    // CTRL_REG5 controls high-pass filtering of outputs, use it
    // if you'd like:
    writeRegister(L3G4200D_ADDRESS, CTRL_REG5, 0b00000000); 
}

uint16_t L3G4200D::getXGyro()
{
    // Rotina para leitura dos valores de X, Y e Z
    uint8_t xMSB = readRegister(L3G4200D_ADDRESS, 0x29);
    uint8_t xLSB = readRegister(L3G4200D_ADDRESS, 0x28);
    uint16_t x = ((xMSB << 8) | xLSB);
    return x;
}

uint16_t L3G4200D::getYGyro()
{
    uint8_t yMSB = readRegister(L3G4200D_ADDRESS, 0x2B);
    uint8_t yLSB = readRegister(L3G4200D_ADDRESS, 0x2A);
    uint16_t y = ((yMSB << 8) | yLSB);
    return y;  
}

uint16_t L3G4200D::getZGyro()
{
  uint8_t zMSB = readRegister(L3G4200D_ADDRESS, 0x2D);
  uint8_t zLSB = readRegister(L3G4200D_ADDRESS, 0x2C);
  uint16_t z = ((zMSB << 8) | zLSB);
  return z;
}

void L3G4200D::writeRegister(uint8_t deviceAddress, uint8_t address, uint8_t val) 
{
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

uint8_t L3G4200D::readRegister(uint8_t deviceAddress, uint8_t address)
{
    uint8_t v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a uint8_t

    while(!Wire.available()) 
    {
        // waiting    Serial.println("flag2");
    }
    v = Wire.read();
    return v;
}
