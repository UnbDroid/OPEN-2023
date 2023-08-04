#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>
#include<MotorDC.h>
#include<Move.h>
#define pd1 A11
#define pd2 A12
#define pe1 9
#define pe2 10
MotorDC LeftMotor(M_LEFT_IN1, M_LEFT_IN2 ,ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_IN3, M_RIGHT_IN4, M_PWM_RIGHT,ENC_A_RIGHT,ENC_B_RIGHT);
LightSensor sensorDireita(A13);
LightSensor sensorEsquerda(A14);
//MotorDC teste(11,12, ENC_A_LEFT, ENC_B_LEFT);

//ESQUERDA pwm A3
//
void TakeMemoryLeftMotor(){ // fica na main
  LeftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  RightMotor.readEncoder();
}
void setup(){
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING);
  pinMode(pd1,OUTPUT);
  pinMode(pd2,OUTPUT);
  pinMode(pe1,OUTPUT);
  pinMode(pe2,OUTPUT);
}

void loop(){
  //movePID(FORWARD, 255 ,&LeftMotor, &RightMotor);
  // Serial.println(RightMotor.getEncoder());
  //LeftMotor.moveForward(255);
  //Serial.println(LeftMotor.getEncoder());
  // Usando o serial, podemos ver o que os encoders estão retornando:l]    
      sensorDireita.read();
      move2(1,&sensorDireita,&sensorEsquerda);
}