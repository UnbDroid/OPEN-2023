#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

#define gyroAdress 0x71
float gy,gx,gz;
void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(gyroAdress);
  Wire.write(0x6C);
  Wire.write(0x00000000);
  Wire.endTransmission();
}
void loop(){
    Wire.beginTransmission(gyroAdress);
    Wire.write(0x03);
    Wire.endTransmission(false);
    Wire.requestFrom(gyroAdress,6, true);
    gx = Wire.read()<<8 | Wire.read();
    gy = Wire.read()<<8 | Wire.read();
    gz = Wire.read()<<8 | Wire.read();

    Serial.println(gx);
    delay(400);

}