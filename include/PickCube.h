#ifndef __PICKCUBE_H
#define __PICKCUBE_H

#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include<Pins.h>
#include <Ultrassonic.h>
#include <Claw.h>
#include <Forklift.h>



int pick_cube_from_right( MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * lateralUltrassonicSensor, LightSensor * rightIR, Ultrassonic * frontalUltrassonicSensor,Claw * RobotClaw, Forklift * Fork);
int pick_cube_from_left( MotorDC * leftMotor, MotorDC * rightMotor, LightSensor * light_LateralLeft);



#endif

