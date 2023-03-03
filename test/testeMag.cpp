#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

#define MPU_ADD 0x68
#define USER_CRTL_add 0x6A
#define INT_BYPASS_CONFIG_AD 0x37
float gy,gx,gz;
void setup(){
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADD);
  Wire.write(USER_CRTL_add);
  Wire.write(0x00, true);
  
}
void loop(){
    Wire.beginTransmission(gyroAdress);
    Wire.write(0x03);
    Wire.endTransmission(false);
    Wire.requestFrom(gyroAdress,6, true);
    gx = float(Wire.read()<<8 | Wire.read())/0.6;
    gy = Wire.read()<<8 | Wire.read();
    gz = Wire.read()<<8 | Wire.read();
    Serial.print("Valor em X ");
    Serial.print(gx);
    Serial.print(" Valor em y ");
    Serial.println(gy);
    Serial.print(" Valor em z ");
    Serial.println(gz);
    delay(400);

}