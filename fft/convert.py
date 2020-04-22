import paho.mqtt.client as mqtt
from dataSet import dataSet

server_addr = "152.66.34.82"
i = 0
dataSets = dict()

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("ESP32-accelerometer/#")

def on_message(client, userdata, msg):
    dataType = msg.topic.split("/")[2]
    device = str(msg.topic.split("/")[1])
    global i
    global dataSets
    if(device in dataSets):
        data = msg.payload.decode("utf-8").split(",")
        dataSets[device].addData(data[1], data[2], data[3], data[0])
    if 'dataFirst' in dataType:
        dataSets[device] = dataSet(device)
        data = msg.payload.decode("utf-8").split(",")
        dataSets[device].addData(data[1], data[2], data[3], data[0])
    elif 'dataEnd' in dataType:
        dataSets[device].fft()
        dataSets[device].createPlots()
        dataSets[device].showPlots()

    


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(server_addr, 1883, 60)

client.loop_forever()

d = dataSet("a")

d.addData(1,2,3,4)
d.addData(0,2,3,5)
d.addData(1,2,3,6)
d.addData(0,2,3,7)
d.addData(1,2,3,8)
d.addData(0,2,3,9)

d.fft()
d.createPlots()
d.saveFftPlot("hello.png")
d.showPlots()