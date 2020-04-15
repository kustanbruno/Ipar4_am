#include <Wire.h>
#include "Arduino.h"

#ifndef vec3_h
#define vec3_h

class vec3{
    public: int16_t x, y, z ;
    vec3();
    vec3(int16_t _x, int16_t _y, int16_t _z);
    void printToSerial();
};

#endif