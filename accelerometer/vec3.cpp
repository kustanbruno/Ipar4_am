 #include "vec3.h"
 
 vec3::vec3(){
        x = 0;
        y = 0;
        z = 0;
    }

vec3::vec3(int16_t _x, int16_t _y, int16_t _z){
    x = _x;
    y = _y;
    z = _z;
}

void vec3::printToSerial(){
        Serial.print(x, DEC);
        Serial.print (",");
        Serial.print(y, DEC);
        Serial.print (",");
        Serial.print(z, DEC);
        Serial.println("");
}

String vec3::toString(){
    String data = "";
    data += x;
    data += ",";
    data += y;
    data += ",";
    data += z;
    return data;
}