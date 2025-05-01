#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to be ready - particularly on Leonardo/Micro boards
  
  Serial.println("Initializing MPU6050...");
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor!");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("MPU6050 sensor found!");
  delay(1000);
}

void loop() {
  // Read acceleration data
  MPU6050::AccelData accel = mpu.readAccel();
  
  // Read gyroscope data
  MPU6050::GyroData gyro = mpu.readGyro();
  
  // Read temperature data
  float temp = mpu.readTemp();
  
  // Print acceleration data (in g)
  Serial.println("Acceleration (g):");
  Serial.print("X: "); Serial.print(accel.x);
  Serial.print("\tY: "); Serial.print(accel.y);
  Serial.print("\tZ: "); Serial.println(accel.z);
  
  // Print gyroscope data (in degrees per second)
  Serial.println("Gyroscope (deg/s):");
  Serial.print("X: "); Serial.print(gyro.x);
  Serial.print("\tY: "); Serial.print(gyro.y);
  Serial.print("\tZ: "); Serial.println(gyro.z);
  
  // Print temperature
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");
  
  Serial.println("-------------------");
  delay(1000);
}