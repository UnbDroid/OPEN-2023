#ifndef __SOL_H
#define __SOL_H

#include<Arduino.h>
#include<LightSensor.h>
#include<Move.h>
#include<MotorDC.h>
#include<math.h>

namespace SOL{
    enum Direcao{Norte=0,Oeste=3,Sul=2,Leste=1};
}
void moveTo(int * xAtual,int *yAtual,int *menorYmenorX,int *direcaoAtual, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor);
int ManhattamDistance(int y1,int x1,int y2,int x2);
int * shortestArea(int notCross,int y,int x);
SOL::Direcao direction(char eixo,int yInicial, int yFinal, SOL::Direcao direcao);
void maquinaDeEstados(int* y,int* x,int *direcaoAtual,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor);
void corrigirDirecao(int * direction, MotorDC * leftMotor,MotorDC* rightMotor);

#endif