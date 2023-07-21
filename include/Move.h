#ifndef MOVE_H
#define MOVE_H

#include <MotorDC.h>

//Liga ambos os motores para moviemntação

void move_forward(MotorDC* motor1, MotorDC* motor2, int velocity);

void move_backward(MotorDC* motor1, MotorDC* motor2, int velocity);
    
void moveForwardPid(MotorDC* motorLeft, MotorDC* motorRight, int velocity);
    

#endif