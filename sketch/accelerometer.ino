#include <Arduino.h>
#include "mpu9250.h"
#include "vec3.h"


void setup(){
    Serial.begin(9600);
}

void loop(){
    mpu.updateGyroscopeAndAccelerometerData();
    vec3 accelerometer = mpu.getAccelerometerData();
    Serial.print ("x:");
    Serial.print(accelerometer.x, DEC);
    Serial.print ("\t y:");
    Serial.print(accelerometer.y, DEC);
    Serial.print ("\t z:");
    Serial.print(accelerometer.z, DEC);
    Serial.println("");
    delay(100);
}