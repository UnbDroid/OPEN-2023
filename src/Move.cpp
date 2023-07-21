#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>

#define Kp 1

void move_forward(MotorDC* motor1, MotorDC* motor2, int velocity){
    motor1->andar_para_frente(velocity);
    motor2->andar_para_frente(velocity);
}
void move_backward(MotorDC* motor1, MotorDC* motor2, int velocity){
    motor1->andar_para_tras(velocity);
    motor2->andar_para_tras(velocity);
}

void moveForwardPid(MotorDC* motorLeft, MotorDC* motorRight, int velocity){
    int posEncoderLeft = motorLeft->getEncoderLeft();
    int posEncoderRight = motorRight->getEncoderRight();

    int erro = posEncoderLeft - posEncoderRight;
    int incremento = erro*Kp;
    int parameterVelocityLeft = velocity - incremento;
    int parameterVelocityRight = velocity + incremento;

    motorLeft->andar_para_frente(parameterVelocityLeft);
    motorLeft->andar_para_frente(parameterVelocityRight);


}

