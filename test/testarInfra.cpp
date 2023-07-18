#include<Arduino.h>
#include"LightSensor.h"
#define PIN_A0      A11
#define pinA02      A12
LightSensor lightSensor(PIN_A0);

void setup(){

    Serial.begin(9600);

}

void loop(){
    Serial.println(lightSensor.read());
}