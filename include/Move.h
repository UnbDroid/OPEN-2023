#ifndef __MOVE_H
#define __MOVE_H
#include<MotorDC.h>
#include<Arduino.h>
#include<MotorDC.h>
#include"MPU9250.h"
#include<LightSensor.h>
#include<LightSensor.h>
#include<Solution.h>

enum Directions{FORWARD, BACKWARD};
enum RotateDirections{LEFT, RIGHT};

void move(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor *lightSensorLeft,LightSensor* lightSensorRight);
void movePID(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight);
void stop(MotorDC* motorLeft, MotorDC* motorRight);
void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight);

void initialPosition(MPU9250 * mpu);
void rotates90(RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight);

void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity);

void moveForSquare(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight);


void correctingDirection(int * direction, MotorDC * leftMotor,MotorDC* rightMotor);
void navegateInRegion(int * currentY,int * currentX,int yDestino, int xDestino,int *destinationYX, int* currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor , int *arrayPosicaoAtual);
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor);
extern int lllla_op;
void moveBackAndCorrectDirection(SOL::Direcao destinationDirection);
//int*currentDirection,MotorDC *leftMotor,MotorDC *rightMotor);
void changingAndCountingosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor);
void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor);


#endif
