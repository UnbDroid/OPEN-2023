#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>

MotorDC LeftMotor(M_LEFT_LPWM, M_LEFT_RPWM,ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM,ENC_A_RIGHT,ENC_B_RIGHT);
LightSensor LeftLightSensor(A0_ESQUERDA_FRENTE);
LightSensor RightLightSensor(A0_ESQUERDA_FRENTE);


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

  // movePID(FORWARD, 150 ,&LeftMotor, &RightMotor);
  // rotates90(LEFT,150,&LeftMotor, &RightMotor);

  // int count = 135;
  // for (int i = 0; i < count; i++)
  // {
  //   LeftMotor.moveForward(i);
  //   RightMotor.moveForward(i);
  //   Serial.println(i);
  // }
  // stop(&LeftMotor,&RightMotor);
  
  // delay(1000);
  // rotates90(LEFT,150,&LeftMotor, &RightMotor);
  // rotates90(LEFT,150,&LeftMotor, &RightMotor);
  // delay(1000);
} 

void loop(){
  movePID(FORWARD, 130 ,&LeftMotor, &RightMotor);  

  // LeftMotor.moveForward(130);
  // RightMotor.moveForward(130);

  // while (analogRead(A0_ESQUERDA_FRENTE) < 100 && analogRead(A0_DIREITA_FRENTE) < 100)
  // {
  //   movePID(FORWARD, 130 ,&LeftMotor, &RightMotor);  
  // }
  
  // movePID(FORWARD, 150 ,&LeftMotor, &RightMotor);
  // stop(&LeftMotor,&RightMotor);


  // Serial.print(analogRead(A0_ESQUERDA_FRENTE));
  // Serial.print(" ");
  // Serial.print(analogRead(A0_DIREITA_FRENTE));
  // Serial.println();



  // Usando o serial, podemos ver o que os encoders estão retornando:
  Serial.print(LeftMotor.getEncoder());
  Serial.print(" ");
  Serial.print(RightMotor.getEncoder());
  Serial.println();


}
