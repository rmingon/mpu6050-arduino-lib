#include "MPU6050.h"

MPU6050::MPU6050(TwoWire &wire) {
  _wire = &wire;
  _addr = MPU6050_ADDR;
}

bool MPU6050::begin() {
  _wire->begin();
  
  // Wake up the MPU6050
  _wire->beginTransmission(_addr);
  _wire->write(MPU6050_REG_PWR_MGMT_1);
  _wire->write(0);  // Set to zero to wake up
  uint8_t error = _wire->endTransmission();
  
  return (error == 0);
}

int16_t MPU6050::readRawValue(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->endTransmission(false);
  
  _wire->requestFrom(_addr, (uint8_t)2);
  
  return (_wire->read() << 8) | _wire->read();
}

MPU6050::AccelData MPU6050::readAccel() {
  AccelData data;
  
  // Read raw accelerometer data
  int16_t rawX = readRawValue(MPU6050_REG_ACCEL_XOUT_H);
  int16_t rawY = readRawValue(MPU6050_REG_ACCEL_XOUT_H + 2);
  int16_t rawZ = readRawValue(MPU6050_REG_ACCEL_XOUT_H + 4);
  
  // Convert to g (assuming +/- 2g range)
  // 16384 LSB/g for +/- 2g range
  data.x = rawX / 16384.0;
  data.y = rawY / 16384.0;
  data.z = rawZ / 16384.0;
  
  return data;
}

MPU6050::GyroData MPU6050::readGyro() {
  GyroData data;
  
  // Read raw gyroscope data
  int16_t rawX = readRawValue(MPU6050_REG_GYRO_XOUT_H);
  int16_t rawY = readRawValue(MPU6050_REG_GYRO_XOUT_H + 2);
  int16_t rawZ = readRawValue(MPU6050_REG_GYRO_XOUT_H + 4);
  
  // Convert to degrees per second (assuming +/- 250 deg/s range)
  // 131 LSB/(deg/s) for +/- 250 deg/s range
  data.x = rawX / 131.0;
  data.y = rawY / 131.0;
  data.z = rawZ / 131.0;
  
  return data;
}

float MPU6050::readTemp() {
  // Read raw temperature data
  int16_t rawTemp = readRawValue(MPU6050_REG_ACCEL_XOUT_H + 6);
  
  // Convert to Celsius
  // Formula from datasheet: Temperature in °C = (TEMP_OUT / 340) + 36.53
  return (rawTemp / 340.0) + 36.53;
}