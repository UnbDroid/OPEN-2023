#include<Arduino.h>
#include"LightSensor.h"
#include<Pins.h>
#include<Mag.h>
#include<MotorDC.h>

MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);

LightSensor sensorDireita(A0_DIREITA_FRENTE);
LightSensor sensorEsquerda(A0_ESQUERDA_FRENTE);

//in3
void TakeMemoryLeftMotor(){ // fica na main
  leftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  rightMotor.readEncoder();
}

Mag mag;
void setup(){
    Serial.begin(9600);
    // Wire.begin();
    // delay(200);
    // if(!mag.setup(0x68)){
    //     while (1) {
    //         Serial.println("Conexão com o MPU FALHOU");
    //     }
    // }
    // mag.setMagneticDeclination(-22.04);
    // mag.setMagBias(216.96,-30.44,0);
    // mag.setMagScale(178.82,160.84,0);
    // Serial.print("X ");
    // Serial.println("Y");
}

void loop(){
    //Serial.println(mag.getDegree());
    leftMotor.moveForward(160);
    rightMotor.moveForward(160);
}