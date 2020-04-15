#include <Arduino.h>
#include "mpu9250.h"
#include "vec3.h"
#include "linkedList.h"

vec3* a;
unsigned long start;
const unsigned long INTERVALL = 1000000;
vec3LinkedList* list = new vec3LinkedList();
int i = 0;

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    start = micros();
    Serial.print("Started");
}

void loop(){
    if(i < 2000){
        mpu.updateGyroscopeAndAccelerometerData();
        vec3 accelerometer = mpu.getAccelerometerData();
        list->pushBack(accelerometer);
        i++;
    }else{
        i=0;
        Serial.println("Data start");
        list->printToSerial();
        Serial.println("Data end");
        delete list;
        list = new vec3LinkedList();
        start = micros();
    }
}