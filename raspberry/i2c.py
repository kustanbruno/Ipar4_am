from mpu9250 import mpu9250
import arrow

sensor = mpu9250()

t = arrow.now()

print(t.microsecond)

list = []

for i in range(2000):
    sensor.updateGyroscopeAndAccelerometerData()
    list.append([arrow.now().microsecond,sensor.accelerometer])

print(list)