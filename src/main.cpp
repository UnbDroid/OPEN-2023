#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>
#include<MotorDC.h>
#include<Move.h>
#define pd1 A11
#define pd2 A12
#define pe1 9
#define pe2 10
MotorDC leftMotor(M_LEFT_RPWM,M_LEFT_LPWM ,ENC_A_RIGHT,ENC_B_RIGHT);
MotorDC rightMotor(A12,A11,ENC_A_RIGHT,ENC_B_RIGHT);
LightSensor sensorDireita(A12);
LightSensor sensorEsquerda(A11);
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
  // pinMode(pd1,OUTPUT);
  // pinMode(pd2,OUTPUT);
  // pinMode(pe1,OUTPUT);
  // pinMode(pe2,OUTPUT);
}

void loop(){
      //move(MOVE::FORWARD)
      sensorDireita.read();
      // if(sensorDireita.getCrossed()){
      //   Serial.println("aaaaaaaaaaaaa");
      //   sensorDireita.setCrossed(false);
      // }
      moveForSquare(1,&sensorDireita,&sensorEsquerda,&leftMotor, &rightMotor);
        //Serial.println(rightMotor.getEncoder());
 
        //rightMotor.moveForward(200);
        
      //move2(1,&sensorDireita,&sensorEsquerda);
}