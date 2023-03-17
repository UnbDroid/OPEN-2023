#include "MPU9250.h"
#include<Arduino.h>

MPU9250 mpu;
float magX_list[200];
float higherX=0;
float lowestY=1000;
float higherY=0;
float lowestX=1000;
void print_roll_pitch_yaw() {
    float heading = atan2(mpu.getMagY(), mpu.getMagX()) * 180.0 / PI;
    if (heading < 0) {
        heading += 360.0;
    }
    float angulo = atan2(mpu.getMagX(), mpu.getMagY());
    Serial.println(angulo*180/PI);
    Serial.print(mpu.getMagX());
    Serial.print(" ");
    Serial.println(mpu.getMagY());
    Serial.println(heading);
}
void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(2000);
    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
        }
    }
    
    mpu.setMagBias(-98.95499999999998,566.49,0.);
    mpu.setMagScale(0.005029801574327893,0.004901720503896868,1.);
    mpu.setMagneticDeclination(-21.091666); //minuto/60; 
    Serial.print('X');  
    Serial.print(" ");
    Serial.println('Y');    

}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }  
    }
}

