
#include "thingProperties.h"
#include <Arduino_LSM6DS3.h>

// Timing variables
unsigned long previousMillis = 0;
const unsigned long interval = 500; 

void setup() {
  Serial.begin(9600);
  delay(1500);
  
  // initialize sensor
  if (!IMU.begin()) {
    Serial.println("Failed to initialize LSM6DS3 IMU!");
    while (1); 
  }
  
  Serial.print("LSM6DS3 Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  
  // initialize arduino cloud properties
  initProperties();
  
  // connect to arduino iot cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  Serial.println("LSM6DS3 Cloud Logger Started!");
}

void loop() {
  // maintain cloud connection
  ArduinoCloud.update();
  
  unsigned long currentMillis = millis();
  
  // read sensor data at specified interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    float x, y, z;
    
    // check if new acceleration data is available
    if (IMU.accelerationAvailable()) {

      IMU.readAcceleration(x, y, z);
      
      // update cloud variables
      accel_x = x;
      accel_y = y; 
      accel_z = z;
      
      // print to Serial Monitor for debugging
      Serial.print("Acceleration (G): X=");
      Serial.print(x, 3);
      Serial.print(", Y=");
      Serial.print(y, 3);
      Serial.print(", Z=");
      Serial.println(z, 3);
    }
  }
}