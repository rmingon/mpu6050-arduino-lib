# MPU6050 Arduino Library

A simple Arduino library for interfacing with the MPU6050 6-axis accelerometer and gyroscope sensor.

## Features

- Easy initialization of the MPU6050 sensor
- Read acceleration data in g (gravity units)
- Read gyroscope data in degrees per second
- Read temperature data in Celsius
- Simple, easy-to-understand API

## Installation

1. Download the library (either clone this repository or download as ZIP)
2. If downloaded as ZIP, extract the contents
3. Place the entire folder in your Arduino libraries directory:
   - Windows: Documents/Arduino/libraries/
   - Mac: Documents/Arduino/libraries/
   - Linux: ~/Arduino/libraries/
4. Restart the Arduino IDE

## Hardware Connection

Connect your MPU6050 to your Arduino board:

| MPU6050 Pin | Arduino Pin      |
|-------------|------------------|
| VCC         | 3.3V             |
| GND         | GND              |
| SCL         | A5 (SCL)         |
| SDA         | A4 (SDA)         |
| INT         | Not used         |

## Usage

```cpp
#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  // Initialize the sensor
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor!");
    while (1) {
      delay(10);
    }
  }
}

void loop() {
  // Read acceleration data
  MPU6050::AccelData accel = mpu.readAccel();
  
  // Read gyroscope data
  MPU6050::GyroData gyro = mpu.readGyro();
  
  // Read temperature
  float temp = mpu.readTemp();
  
  // Use the data as needed...
  Serial.print("Accel X: ");
  Serial.println(accel.x);
  
  delay(1000);
}