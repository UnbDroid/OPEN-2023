#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>

#define DIR 53//49
#define PUL 51//47

void setup() {
  // set the speed at 60 rpm:
  //myStepper.setSpeed(60);
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  // initialize the serial port:
  Serial.begin(9600);
  digitalWrite(DIR, LOW);
}

#define PPS 400 //velocidade: passo por segundo
#define DELAY_PPS (500/PPS) //1 segundo dividido pela velocidade


int posicao = 500; // fazer o teste de quanto isso equivale em mm

void loop() {
  // digitalWrite(DIR, !digitalRead(DIR));
  for (int i = 0; i<posicao; i++)
  {
    digitalWrite(PUL, HIGH);
    delay(DELAY_PPS);
    digitalWrite(PUL, LOW);
    delay(DELAY_PPS);
  }
  delay(1000);
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