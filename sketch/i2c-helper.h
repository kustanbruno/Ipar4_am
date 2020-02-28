#ifndef i2c_h
#define i2c_h

#include <Wire.h>

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

#endif