#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>
#include <StepMotor.h>
#include <Claw.h>
#include <Forklift.h> 


Claw Robot_Claw(DIR_GARRA, PUL_GARRA);
Forklift emp(DIR_EMPILHADEIRA, PUL_EMPILHADEIRA);

void setup() {
  Serial.begin(9600);
  Serial.println("Olá");
  delay(5000);
  // Robot_Claw.close_claw_distance_cm(9.5);

  emp.forklift_up_distance_cm(14);
}



void loop() {
  // emp.forklift_up_distance_cm(100);
  // Robot_Claw.open_claw_distance_cm(15);
}