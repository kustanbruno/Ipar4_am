#include "mpu9250.h";

mpu9250::mpu9250(){
    Wire.begin();
    // Set accelerometers low pass filter at 5Hz
    I2CwriteByte(MPU9250_ADDRESS,29,0x06);
    // Set gyroscope low pass filter at 5Hz
    I2CwriteByte(MPU9250_ADDRESS,26,0x06);
    // Configure gyroscope range
    I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_1000_DPS);
    // Configure accelerometers range
    I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
    // Set by pass mode for the magnetometers
    I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);
    // Request continuous magnetometer measurements in 16 bits
    I2CwriteByte(MAG_ADDRESS,0x0A,0x16);
}

void mpu9250::readAccelerometer(){
    accelermeter.x = -(Buf[0]<<8 | Buf[1]);
    accelermeter.y = -(Buf[2]<<8 | Buf[3]);
    accelermeter.z = Buf[4]<<8 | Buf[5];
}

void mpu9250::readGyroscope(){
    gyroscope.x = -(Buf[8]<<8 | Buf[9]); 
    gyroscope.y = -(Buf[10]<<8 | Buf[11]);
    gyroscope.z = Buf[12]<<8 | Buf[13];
}

void mpu9250::readMagnetometer(){
    megnetometer.x=-(Mag[3]<<8 | Mag[2]);
    megnetometer.y=-(Mag[1]<<8 | Mag[0]);
    megnetometer.z=-(Mag[5]<<8 | Mag[4]);
}

void mpu9250::updateMagnetometerData(){
    uint8_t ST1;
    do{
        I2Cread(MAG_ADDRESS,0x02,1,&ST1);
    }
    while (!(ST1&0x01));
    I2Cread(MAG_ADDRESS,0x03,7,Mag);
}

void mpu9250::updateGyroscopeAndAccelerometerData(){
    I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
    readAccelerometer();
    readGyroscope();
}

vec3 mpu9250::getAccelerometerData(){
    return accelermeter;
}

vec3 mpu9250::getGyroscopeData(){
    return gyroscope;
}

vec3 mpu9250::getMagnetometerData(){
    return accelermeter;
}

mpu9250::~mpu9250(){
}

mpu9250 mpu = mpu9250();