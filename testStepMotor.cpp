#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>



void setup() {
  // set the speed at 60 rpm:
  //myStepper.setSpeed(60);
  pinMode(DIR_GARRA, OUTPUT);
  pinMode(PUL_GARRA, OUTPUT);

  // initialize the serial port:
  Serial.begin(9600);
  digitalWrite(DIR_GARRA, LOW); /* LOW SOBE*/
  Serial.println("ola");
  delay(4000);
}

#define PPS 400 //velocidade: passo por segundo
#define DELAY_PPS (500/PPS) //1 segundo dividido pela velocidade


int posicao = 1200; // fazer o teste de quanto isso equivale em mm

void loop() {
  Serial.println("oi");
  digitalWrite(DIR_GARRA, !digitalRead(DIR_GARRA));
  for (int i = 0; i<posicao; i++)
  {
    digitalWrite(PUL_GARRA, HIGH);
    delay(DELAY_PPS);
    digitalWrite(PUL_GARRA, LOW);
    delay(DELAY_PPS);
    // Serial.println(i);
  }
  // delay(1000);
  /*
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  */
}