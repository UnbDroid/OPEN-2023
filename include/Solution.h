#ifndef __SOL_H
#define __SOL_H

#include<Arduino.h>
#include<LightSensor.h>
#include<MotorDC.h>
#include<math.h>
#include<Claw.h>
#include<Forklift.h>
#include<Ultrassonic.h>

namespace SOL{
    enum Direcao{Norte=0,Oeste=3,Sul=2,Leste=1};
}

int manhattamDistance(int y1,int x1,int y2,int x2);
int * shortestArea(bool cross,int y,int x);
SOL::Direcao direction(char eixo,int yInicial, int yFinal, SOL::Direcao direcao);
void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,Claw*robotClaw, Forklift * forkLift, Ultrassonic * lateralUltrassonic,Ultrassonic*frontalUltrassonic,LightSensor * middleSensor);
SOL::Direcao futureDirection(char axis,int start, int final);
int * deliveryPlace(int y,int x,int blockType);
#endif