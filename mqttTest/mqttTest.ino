#include "WiFi.h"
#include <PubSubClient.h>
#include "Arduino.h"

const char *ssid = "kustan";
const char *password = "nemROVIDpass@2017";
const char *mqtt_server = "152.66.34.82";

WiFiClient wifi_client;
PubSubClient client(wifi_client);
unsigned long currentTime;

void connectToWifi()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    IPAddress ip = WiFi.localIP();
    Serial.println("Connected to the WiFi network");
    Serial.print("ip: ");
    Serial.print(ip);
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1')
    {
        digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
                                        // but actually the LED is on; this is because
                                        // it is active low on the ESP-01)
    }
    else
    {
        digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
    }
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP32-Accelerometer";
        //clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("ESP32-accelerometer/outTopic", "hello world");
            // ... and resubscribe
            client.subscribe("ESP32-accelerometer/inTopic");
            client.subscribe("ESP32-accelerometer/inTopicc");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup()
{

    Serial.begin(115200);
    connectToWifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    currentTime = millis();
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    if (millis() > currentTime + 5000)
    {
        currentTime = millis();
        client.publish("ESP32-accelerometer/outTopic", "5s elapsed");
    }
}