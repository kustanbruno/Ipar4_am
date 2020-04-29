from influxdb import InfluxDBClient

client = InfluxDBClient(host = '152.66.34.82', port = 8086 )
dbs = client.get_list_database()
foundAccelerometerDB = False

for db in dbs:
    if db['name'] == 'Accelerometer':
        foundAccelerometerDB = True

if not foundAccelerometerDB:
    client.create_database('Accelerometer')

client.switch_database('Accelerometer')

json = [
    {
        "measurement": "CNC1",
        "tags": {
            "deviceName": "accelerometer1"
        },
        "time": "2020-04-29 19:00",
        "fields": {
            "kaga": "kk"
        }
    }
]

client.write_points(json)