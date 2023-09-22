#ifndef __MOVE_H
#define __MOVE_H
#include<MotorDC.h>
#include<Arduino.h>
#include<MotorDC.h>
#include"MPU9250.h"
#include<LightSensor.h>
#include<LightSensor.h>


enum Directions{FORWARD, BACKWARD};
enum RotateDirections{LEFT, RIGHT, AROUND};

void move(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor *lightSensorLeft,LightSensor* lightSensorRight);
void movePID(Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight);
void stop(MotorDC* motorLeft, MotorDC* motorRight);
void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight);
void setPreviusTime(int value);
double getPreviusTime();


void initialPosition(MPU9250 * mpu);
void rotates(RotateDirections rotateDirection,MotorDC * motorLeft, MotorDC * motorRight);
// void rotates180(RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight);
void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity);

void moveForSquare(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight);
void move2(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight);
void correctingDirection(int * direction, MotorDC * leftMotor,MotorDC* rightMotor);
#endif
