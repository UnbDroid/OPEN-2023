#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>
#include<Mag.h>

Mag mag;
void setup(){
    Serial.begin(9600);
    Wire.begin();
    delay(200);
    if(!mag.setup(0x68)){
        while (1) {
            Serial.println("Conexão com o MPU FALHOU");
        }
    }
    mag.setMagneticDeclination(-21.96);
    mag.setMagBias(343.46,-13.32,0);
    mag.setCorrection(6);
    mag.setMagScale(194.51,191.10,0);
}

void loop(){
    Serial.println(mag.getDegree());
}