#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>

MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor CentralColorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
LightSensor sensorDireita(A0_DIREITA_FRENTE);
LightSensor sensorEsquerda(A0_ESQUERDA_FRENTE);

//in3
void TakeMemoryLeftMotor(){ // fica na main
  leftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  rightMotor.readEncoder();
}
void setup()
{
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING); // deixa na main
  // rotates90(RIGHT,160,&leftMotor,&rightMotor);
}
int a = Directions::BACKWARD;
int dir = 2;
int y =6;
int x =7;
int direcaoAtual = SOL::Norte;
void loop(){

  maquinaDeEstados(&y,&x,&direcaoAtual,&sensorEsquerda,&sensorDireita,&leftMotor,&rightMotor);
  // sensorDireita.read();
  // sensorEsquerda.read();
  // if(sensorDireita.getCrossed()){
  //   Serial.println("direita atravessou");
  //   sensorDireita.setCrossed(false);
  // }
  // else if(sensorEsquerda.getCrossed()){
  //   Serial.println("esquerda atravessou");
  //   sensorEsquerda.setCrossed(false);
  // }
}

