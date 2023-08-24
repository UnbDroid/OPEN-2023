#ifndef __SOL_H
#define __SOL_H

#include<Arduino.h>
#include<LightSensor.h>
#include<Move.h>
#include<MotorDC.h>
#include<math.h>

namespace SOL{
    enum Direcao{Norte,Sul,Leste,Oeste};
}
int ManhattamDistance(int y1,int x1,int y2,int x2);
int * shortestArea(int y,int x);
SOL::Direcao direction(char eixo,int yInicial, int yFinal, SOL::Direcao direcao){

#endif