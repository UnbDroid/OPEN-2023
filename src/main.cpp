#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>

LightSensor sensorDireita(A13);
LightSensor sensorEsquerda(A14);
void setup(){
    Serial.begin(9600);

}

void loop(){
    sensorEsquerda.read();
    sensorDireita.read();
    if(sensorEsquerda.getCrossed()){
        Serial.println("Esquerda Atravessou");
    }
    else if(sensorDireita.getCrossed()){
        Serial.println("Direita Atravessou");
    }
}

