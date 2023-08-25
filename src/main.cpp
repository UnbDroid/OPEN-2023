#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>

MotorDC LeftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);

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
  
  pinMode(A0_DIREITA_FRENTE, INPUT);
  pinMode(A0_ESQUERDA_FRENTE, INPUT);
  
  // pinMode(EN_LEFT_MOTOR, OUTPUT);
  // pinMode(M_LEFT_RPWM,OUTPUT);
  // pinMode(M_LEFT_LPWM,OUTPUT);

  // pinMode(EN_RIGHT_MOTOR, OUTPUT);
  // pinMode(M_RIGHT_RPWM,OUTPUT);
  // pinMode(M_RIGHT_LPWM,OUTPUT);

  // digitalWrite(M_RIGHT_RPWM, HIGH);
  // digitalWrite(M_RIGHT_LPWM,LOW);
  // analogWrite(EN_RIGHT_MOTOR, 130);
  
  
  // int count = 150;
  // for (int i = 30; i < count; i++)
  // {
  //   movePID(FORWARD,i,&LeftMotor,&RightMotor);  
  //   delay(100);
  //   Serial.println(i);
  // }
  
  // movePID(FORWARD,128,&LeftMotor,&RightMotor);
  // LeftMotor.moveForward(255);
  // RightMotor.moveForward(255);
  // delay(1000);
  // stop(&LeftMotor,&RightMotor);
  // delay(1400);
  // stop(&LeftMotor,&RightMotor);
  // delay(1000);
  
  // delay(1000);
  // while (analogRead(A0_DIREITA_FRENTE) < 40 && analogRead(A0_ESQUERDA_FRENTE) < 40)
  // {
  //   movePID(FORWARD,70,&LeftMotor,&RightMotor); 
  // }
  // stop(&LeftMotor,&RightMotor);
  
  // int count = 200;
  // for (int i = 130; i < count; i++)
  // {
  //   movePID(FORWARD,i,&LeftMotor,&RightMotor); 
  //   delay(50);
  // }
  
  
  


} 

void loop(){
  rotates90(RIGHT, 130, &LeftMotor, &RightMotor);
  rotates90(RIGHT, 130, &LeftMotor, &RightMotor);
  stop(&LeftMotor,&RightMotor);
  delay(1000);
  
  // Serial.print(analogRead(A0_DIREITA_FRENTE));
  // Serial.print(" ");
  // Serial.print(analogRead(A0_ESQUERDA_FRENTE));
  // Serial.println();
  // // // Usando o serial, podemos ver o que os encoders estão retornando:
  // Serial.print(LeftMotor.getEncoder());
  // Serial.print(" ");
  // Serial.print(RightMotor.getEncoder());
  // Serial.println();


}
