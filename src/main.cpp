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
    mpu.setMagBias(5446.005,628.4300000000001,0.);
    mpu.setMagScale(0.00018362083765989932,-0.054884742041712405,1.);
    mpu.setMagneticDeclination(-21.091666); //minuto/60;
    Serial.print("Mag X, ");
    Serial.println("Mag y " );    

<<<<<<< HEAD
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }  
=======
    mpu.setup(0x68);  // change to your own address
    mpu.setMagneticDeclination(-21.091666); //minuto/60
    mpu.setMagBias(1,0,0);
}

float Norte = 5.5;//6.5;
float leste = 25;//30;
float oeste = 14;//19;
float sul = 32;//37
void loop() {
    if (mpu.update()) {
      
       Serial.println(mpu.getYaw());
       //Serial.println(((pow(pow(anguloReal,2)+ pow(angulo2, 2), 0.5))*180)/PI);
>>>>>>> e2f0f193bd91116825c18b88009f1fcb15b04076
    }
}

