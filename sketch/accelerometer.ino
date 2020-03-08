#include <Arduino.h>
#include "mpu9250.h"
#include "vec3.h"
#include "linkedList.h"

vec3* a;
unsigned long start;
const unsigned long INTERVALL = 1000000;
vec3LinkedList* list = new vec3LinkedList();


void setup(){
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    start = micros();
}

void loop(){
    if(micros() - start < INTERVALL){
        mpu.updateGyroscopeAndAccelerometerData();
        vec3 accelerometer = mpu.getAccelerometerData();
        list->pushBack(accelerometer);
    }else{
        Serial.println("Data start");
        list->printToSerial();
        Serial.println("Data end");
        delete list;
        list = new vec3LinkedList();
        start = micros();
    }
}