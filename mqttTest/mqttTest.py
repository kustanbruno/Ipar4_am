import paho.mqtt.client as mqtt
from pprint import pprint


server_addr = "152.66.34.82"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("ESP32-accelerometer/#")

def on_message(client, userdata, msg):
    print(client)
    print(msg.topic+" "+str(msg.payload))


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(server_addr, 1883, 60)

client.loop_forever()