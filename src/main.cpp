#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>

MotorDC LeftMotor(M_LEFT_LPWM, M_LEFT_RPWM,ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM,ENC_A_RIGHT,ENC_B_RIGHT);

void TakeMemoryLeftMotor(){ // fica na main
  LeftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  RightMotor.readEncoder();
}

void setup()
{
  Serial.begin(9600); 

  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING); // deixa na main

} 

void loop(){

  // Usando o serial, podemos ver o que os encoders estão retornando:
  // Serial.print(LeftMotor.getEncoder());
  // Serial.print(" ");
  // Serial.print(RightMotor.getEncoder());
  // Serial.println();

}
