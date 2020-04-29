#include <EasyNTPClient.h>

#include <Arduino.h>
#include "mpu9250.h"
#include "vec3.h"
#include "linkedList.h"
#include "WiFi.h"
#include <PubSubClient.h>
#include <NTPClient.h>

//CONFIG
const char *ssid = "kustan";
const char *password = "nemROVIDpass@2017";
const char *mqtt_server = "152.66.34.82";
const String deviceName = "Accelerometer-01";
const long utcOffsetInSeconds = 3600;
const char *ntpServer = "0.hu.pool.ntp.org";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);
unsigned long currentTime;
long absoluteTime;

unsigned long start;
vec3LinkedList* list = new vec3LinkedList();
int i = 0;

void connectToWifi(){
    WiFi.begin(ssid, password);

    Serial.println("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(" ..");
    }

    IPAddress ip = WiFi.localIP();
    Serial.println("Connected to WiFi");
    Serial.println("ip: ");
    Serial.print(ip);
}


void callback(char *topic, byte *payload, unsigned int length){
    //ezt most nem használjuk
}

void reconnect(){
    while (!mqtt_client.connected()){
        Serial.print("Attempting MQTT connection...");    
        if (mqtt_client.connect(deviceName.c_str())){
            Serial.println("connected to MQTT broker");
        }
        else{
            Serial.print("failed, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            //túlzásnak érzem
            delay(5000);
        }
    }
}

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    connectToWifi();
    digitalWrite(2, HIGH);

    mqtt_client.setServer(mqtt_server, 1883);
    mqtt_client.setCallback(callback);
    
    start = micros();
    Serial.println("Started");
}

void mqttConnectionHealth(){
    if (!mqtt_client.connected())
        reconnect();
    mqtt_client.loop();
}

void loop(){
    mqttConnectionHealth();
    if(i == 0){
        timeClient.update();
        absoluteTime = timeClient.getEpochTime();
    }
    if(i < 2000){
        mpu.updateGyroscopeAndAccelerometerData();
        vec3 accelerometer = mpu.getAccelerometerData();
        list->pushBack(accelerometer);
        i++;
    }else{
        Serial.println(timeClient.getEpochTime());
        i=0;
        Serial.println("publishing");
        list->setTime(absoluteTime);
        list->uploadToMQTT(mqtt_client, deviceName);
        Serial.println("published");
        delete list;
        list = new vec3LinkedList();
        start = micros();
        timeClient.update();
        absoluteTime = timeClient.update();
    }
}