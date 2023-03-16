#include "MPU9250.h"
#include<Arduino.h>

MPU9250 mpu;
float magX_list[200];
float higherX=0;
float lowestY=1000;
float higherY=0;
float lowestX=1000;
void print_roll_pitch_yaw() {
    
    // float angulo = atan2(mpu.getMagX(), mpu.getMagY());
    // Serial.println(angulo*180/PI);
    Serial.print(mpu.getMagX());
    Serial.print(" ");
    Serial.println(mpu.getMagY());
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
    mpu.setMagBias(-0.020000000000000018,-18.21500000000000,0.);
    mpu.setMagScale(-49.99999999999996,1.,1.);
    mpu.setMagneticDeclination(-21.091666); //minuto/60;
    Serial.print("Mag X, ");
    Serial.println("Mag y " );    

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

