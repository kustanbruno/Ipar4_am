#include <Arduino.h>
#include "mpu9250.h"
#include "vec3.h"
#include "linkedList.h"
#include "WiFi.h"
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUDP.h>

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
vec3LinkedList* list1 = new vec3LinkedList();
vec3LinkedList* list2 = new vec3LinkedList();
int i = 0;

TaskHandle_t Task1;
TaskHandle_t Task2;

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

    //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
    xTaskCreatePinnedToCore(
                      collectingCore,   /* Task function. */
                      "Task1",     /* name of task. */
                      10000,       /* Stack size of task */
                      NULL,        /* parameter of the task */
                      1,           /* priority of the task */
                      &Task1,      /* Task handle to keep track of created task */
                      0);          /* pin task to core 0 */                  

    //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
    xTaskCreatePinnedToCore(
                      uploadingCore,   /* Task function. */
                      "Task2",     /* name of task. */
                      10000,       /* Stack size of task */
                      NULL,        /* parameter of the task */
                      1,           /* priority of the task */
                      &Task2,      /* Task handle to keep track of created task */
                      1);          /* pin task to core 1 */
    
    Serial.println("Started");
}

void mqttConnectionHealth(){
    if (!mqtt_client.connected())
        reconnect();
    mqtt_client.loop();
}

void collect(vec3LinkedList* list){
    timeClient.update();
    absoluteTime = timeClient.getEpochTime();
    list->setTime(absoluteTime);
    while(i < 2000){
        mpu.updateGyroscopeAndAccelerometerData();
        vec3 accelerometer = mpu.getAccelerometerData();
        list->pushBack(accelerometer);
        i++;
        yield();
    }
}

void collectingCore(void * pvParameters){
    while(true){
        i = 0;
        if(list1->empty){
            list1->empty = false;
            Serial.println("collecting to list1");
            collect(list1);
            Serial.println("collected to list1");
            list1->readyToUpload=true;
        }else if(list2->empty){
            list2->empty = false;
            Serial.println("collecting to list2");
            collect(list2);
            Serial.println("collected to list2");
            list2->readyToUpload = true;
        }
        yield();
    }
}

void uploadingCore(void * pvParameters){
    while(true){
        mqttConnectionHealth();
        if(list1->readyToUpload){
            Serial.println("publishing list1");
            list1->uploadToMQTT(mqtt_client, deviceName);
            Serial.println("published list1");
            delete list1;
            list1 = new vec3LinkedList();
        }else if(list2->readyToUpload){
            Serial.println("publishing list2");
            list2->uploadToMQTT(mqtt_client, deviceName);
            Serial.println("published list2");
            delete list2;
            list2 = new vec3LinkedList();
        }
        yield();
    }
}

void loop(){
}
