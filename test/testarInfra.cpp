#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>

LightSensor lightSensorDireitaFrente(A0_DIREITA_FRENTE);
LightSensor lightSensorEsquerdaFrente(A0_ESQUERDA_FRENTE);
LightSensor lightSensorDireitaMeio(A0_DIREITA_MEIO);
LightSensor lightSensorEsquerdaMeio(A0_ESQUERDA_MEIO);

void setup(){

    Serial.begin(9600);

}

void loop(){
    // Serial.print(" EsquerdaFrente ");
    // Serial.print(lightSensorEsquerdaFrente.read());
    // Serial.print(" DireitaFrente ");
    // Serial.println(lightSensorDireitaFrente.read());
    Serial.print("aaaaaaaaa ");
    Serial.print("aaaaaaaaa ");
    Serial.print(lightSensorDireitaFrente.lastestChanges[0]);
    Serial.print(lightSensorDireitaFrente.lastestChanges[1]);
    Serial.println(lightSensorDireitaFrente.lastestChanges[2]);
}