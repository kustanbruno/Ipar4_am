from smbus import SMBus

MPUADDRESS = 0x68
MAGADDRESS = 0x0c

class vec3: 
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
    
    def __str__(self):
        return "{},{},{}\n".format(self.x, self.y, self.z)
    
    def __repr__(self):
        return "{},{},{}".format(self.x, self.y, self.z)


class mpu9250:
    def __init__(self):
        self.accelerometer = vec3()
        self.gyroscope = vec3()
        self.bus = SMBus(1)
        self.bus.open(1)
        # Set accelerometers low pass filter at 5Hz
        self.bus.write_byte_data(MPUADDRESS,29,6)
        # Set gyroscope low pass filter at 5Hz
        self.bus.write_byte_data(MPUADDRESS,26,6)
        # Configure gyroscope range
        self.bus.write_byte_data(MPUADDRESS,27,10)
        # Configure accelerometers range
        self.bus.write_byte_data(MPUADDRESS,28,8)
        # Set by pass mode for the magnetometers
        self.bus.write_byte_data(MPUADDRESS,37,2)
        # Request continuous magnetometer measurements in 16 bits
        #self.bus.write_byte_data(MAGADDRESS,0x0A,0x16)

    def updateGyroscopeAndAccelerometerData(self):
        data = self.bus.read_i2c_block_data(MPUADDRESS, 0x3b, 14)
        self.accelerometer.x =-(data[0]<<8 | data[1])
        self.accelerometer.y = -(data[2]<<8 | data[3])
        self.accelerometer.z = data[4]<<8 | data[5]
        self.gyroscope.x = -(data[8]<<8 | data[9])
        self.gyroscope.y = -(data[10]<<8 | data[11])
        self.gyroscope.z = data[12]<<8 | data[13]
