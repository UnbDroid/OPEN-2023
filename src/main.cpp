#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>

MotorDC LeftMotor(M_LEFT_IN1, M_LEFT_IN2, PWM_LEFT,ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_IN3, M_RIGHT_IN4, M_PWM_RIGHT,ENC_A_RIGHT,ENC_B_RIGHT);
LightSensor sensorDireita(A13);
LightSensor sensorEsquerda(A14);
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

void loop()
{
sensorDireita.read();
sensorEsquerda.read();

moveForSquare(1,&sensorDireita,&sensorEsquerda,&LeftMotor,&RightMotor);
// movePID(FORWARD, 255 ,&LeftMotor, &RightMotor);
//     Serial.println(sensorDireita.read());
    

// Usando o serial, podemos ver o que os encoders estão retornando:
// Serial.print(LeftMotor.getEncoder());
// Serial.print(" ");
// Serial.print(RightMotor.getEncoder());
// Serial.println();


}
