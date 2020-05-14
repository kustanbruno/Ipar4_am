import paho.mqtt.client as mqtt
from dataSet import dataSet
from influxdb import InfluxDBClient

mqtt_addr = "152.66.34.82"
influx_addr = mqtt_addr
databaseName = "Accelerometer"

dataSets = dict()
influxClient = InfluxDBClient(host = influx_addr, port = 8086 )
influxClient.switch_database('Accelerometer')

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("ESP32-accelerometer/#")

def on_message(client, userdata, msg):
    dataType = msg.topic.split("/")[2]
    device = str(msg.topic.split("/")[1])
    global dataSets
    global influx_addr
    global influxClient
    if device in dataSets:
        if 'startTime' in dataType:    
            dataSets[device].startTime = int(msg.payload.decode("utf-8"))
            dataSets[device].createPlots()
            dataSets[device].showPlots()
            #dataSets[device].sendToInfluxDB(databaseName)
            return
        data = msg.payload.decode("utf-8").split(",")
        dataSets[device].addData(data[1], data[2], data[3], data[0])
    if 'dataFirst' in dataType:
        dataSets[device] = dataSet(device)
        data = msg.payload.decode("utf-8").split(",")
        dataSets[device].addData(data[1], data[2], data[3], data[0])        
        dataSets[device].influxConnection = influxClient
    elif 'dataEnd' in dataType:
        dataSets[device].fft()
    
mqttClient = mqtt.Client()
mqttClient.on_connect = on_connect
mqttClient.on_message = on_message

mqttClient.connect(mqtt_addr, 1883, 60)
mqttClient.loop_forever()