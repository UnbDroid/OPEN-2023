#ifndef __MOVE_H
#define __MOVE_H
#include<MotorDC.h>
#include<Arduino.h>
#include<MotorDC.h>
#include"MPU9250.h"
#include<LightSensor.h>
#include<LightSensor.h>
namespace MOVE{
    enum Directions{FORWARD, BACKWARD};
    enum RotateDirections{LEFT, RIGHT};
}
void move(MOVE::Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor *lightSensorLeft,LightSensor* lightSensorRight);
void movePID(MOVE::Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight);
void initialPosition(MPU9250 * mpu);
void rotates90(MOVE::RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight);
void rotates180(MOVE::RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight);
void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity);

void moveForSquare(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight);
void move2(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight);

#endif
