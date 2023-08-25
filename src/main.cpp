#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>
#include<MotorDC.h>
#include<Move.h>
#define pd1 A11
#define pd2 A12
#define pe1 9
#define pe2 10
MotorDC leftMotor(M_LEFT_RPWM,M_LEFT_LPWM ,18,19);
MotorDC rightMotor(A5,A6,3,2);
LightSensor sensorEsquerda(A12);
LightSensor sensorDireita(A11);
//MotorDC teste(11,12, ENC_A_LEFT, ENC_B_LEFT);

//in3
void TakeMemoryLeftMotor(){ // fica na main
  leftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  rightMotor.readEncoder();
}
void setup(){
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING);
  
}

void loop(){
  
}