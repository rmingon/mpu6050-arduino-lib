#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>
#include <Wire.h>

#define MPU6050_ADDR         0x68  // MPU6050 I2C address
#define MPU6050_REG_PWR_MGMT_1 0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_GYRO_XOUT_H  0x43

class MPU6050 {
  public:
    // Structures to store sensor data
    struct AccelData {
      float x;
      float y;
      float z;
    };
    
    struct GyroData {
      float x;
      float y;
      float z;
    };

    // Constructor
    MPU6050(TwoWire &wire = Wire);
    
    // Initialize the sensor
    bool begin();
    
    // Read acceleration data (in g: 9.81 m/s^2)
    AccelData readAccel();
    
    // Read gyroscope data (in degrees per second)
    GyroData readGyro();
    
    // Read temperature data (in °C)
    float readTemp();
    
  private:
    TwoWire *_wire;
    uint8_t _addr;
    
    // Read raw sensor data
    int16_t readRawValue(uint8_t reg);
};

#endif