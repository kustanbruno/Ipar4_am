#ifndef mpu9250_h
#define mpu9250_h

#include <Wire.h>
#include "vec3.h"
#include "i2c-helper.h"

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

class mpu9250{
private:
    vec3 accelermeter, gyroscope, megnetometer;
    uint8_t Buf[14];
    uint8_t Mag[7];
    void readGyroscope();
    void readAccelerometer();
    void readMagnetometer();
public:
    mpu9250();
    void updateGyroscopeAndAccelerometerData();
    void updateMagnetometerData();
    vec3 getAccelerometerData();
    vec3 getGyroscopeData();
    vec3 getMagnetometerData();
    ~mpu9250();
};

extern mpu9250 mpu;

#endif