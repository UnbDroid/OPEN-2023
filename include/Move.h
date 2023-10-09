#ifndef __MOVE_H
#define __MOVE_H
#include<MotorDC.h>
#include<Arduino.h>
#include<MotorDC.h>
#include"MPU9250.h"
#include<LightSensor.h>
#include<LightSensor.h>
#include<Solution.h>
#include <Bumper.h>
#include <LDR.h>

enum Directions{FORWARD, BACKWARD};
enum RotateDirections{LEFT, RIGHT, AROUND};

void move(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor *lightSensorLeft,LightSensor* lightSensorRight);
void movePID(Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight);
void move_cm(int distance_cm, Directions direction,MotorDC* motorLeft, MotorDC* motorRight);
void stop(MotorDC* motorLeft, MotorDC* motorRight);
void stopLow(MotorDC* motorLeft, MotorDC* motorRight);
void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight);
void setPreviusTime(double value);
void calibrateMotorsCT(MotorDC * leftMotor, MotorDC * rightMotor);
double getPreviusTime();
double add(double * ptr, double valor);
void boucing(MotorDC* leftMotor, MotorDC* rightMotor, LightSensor * leftIR, LightSensor * rightIR, LightSensor * middleLeftIR, LightSensor * middleRightIR, Bumper * bumper);
void boucing(MotorDC* leftMotor, MotorDC* rightMotor, LightSensor * leftIR, LightSensor * rightIR, LightSensor * middleLeftIR, LightSensor * middleRightIR);





void rotates(RotateDirections rotateDirection,MotorDC * motorLeft, MotorDC * motorRight);


void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity);
void align(LightSensor * leftIR, LightSensor *rightIR, MotorDC * motorLeft, MotorDC * motorRight, int PWM,LightSensor *middleIRDireita, LightSensor *middleIrEsquerda);
void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleLeftIR, LightSensor * middleRightIR);

void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensor, LightSensor * backIr);
void moveBackAndCorrectDirection(SOL::Direcao destinationDirection,int*currentDirection,MotorDC *leftMotor,MotorDC *rightMotor);

void changingAndCountingosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensor);

void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensor,LightSensor*backIR);
void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensor,LightSensor*backIr,LightSensor*middleSensorleft);

void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensor,LightSensor*backIr,LightSensor*middleSensorLeft);

void correctDirection(int* atual,int destino,MotorDC * leftMotor, MotorDC * rightMotor);


int beginning(LightSensor * lightSensorLeft, LightSensor * lightSensorRight, LightSensor * middleLeftIR,LightSensor * middleRightIR ,LightSensor * backIR, MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * frontalUltrassonic, Ultrassonic * lateralUltrassonic,Bumper * bumper, LDR * ldr);
void changingAndCountingPosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensorRight,LightSensor * middleSensorLeft);

void move_cm(int distance_cm, MotorDC* motorLeft, MotorDC* motorRight,LightSensor * leftIr,LightSensor * rightIr,LightSensor*middleSensorRight);


void moveToSquareByCm(int distance,MotorDC*leftMotor, MotorDC*rightMotor, LightSensor * leftIR,LightSensor*rightIR,LightSensor *rightMiddleIR,LightSensor * backIR);
void changingAndCountingPosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * middleSensorRight,LightSensor * middleSensorLeft,LightSensor * backIr);
void moveToSquareByCm(int distance,MotorDC*leftMotor, MotorDC*rightMotor, LightSensor * leftIR,LightSensor*rightIR,LightSensor *rightMiddleIR,LightSensor * backIR,LightSensor * leftMiddleIR);
#endif
