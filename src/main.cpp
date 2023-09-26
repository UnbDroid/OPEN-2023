#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Solution.h>

#include <StepMotor.h>
#include <Claw.h> 
#include <Forklift.h> 
#include <Rasp.h>

#include <PickCube.h>
#include <Ultrassonic.h>


Claw Robot_Claw(DIR_GARRA, PUL_GARRA);
Forklift forklift(DIR_EMPILHADEIRA, PUL_EMPILHADEIRA);
MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor CentralColorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
LightSensor rightIR(A0_DIREITA_FRENTE);
LightSensor leftIR(A0_ESQUERDA_FRENTE);
LightSensor lateral_leftIR(A0_LATERAL_LEFT);
LightSensor lateral_rightIR(A0_LATERAL_RIGHT);
Ultrassonic frontalUltrassonicSensor(echo_ultrassom_frontal, trig_ultrassom_frontal);
Ultrassonic lateralUltrassonicSensor(echo_ultrassom_lateral, trig_ultrassom_lateral);


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


}
int y=6;
int x =7;
int direcao=SOL::Norte;

void loop(){
  stateMachine(&y,&x,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&Robot_Claw,&forklift,&lateralUltrassonicSensor,&frontalUltrassonicSensor);
  }




