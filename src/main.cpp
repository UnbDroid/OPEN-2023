#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Solution.h>
#include<Ultrassonic.h>
#include <Bumper.h>
#include <StepMotor.h>
#include <Claw.h> 
#include <Forklift.h> 
#include <Rasp.h>
#include <PickCube.h>
#include <Ultrassonic.h>
#include <LDR.h>


Claw Robot_Claw(DIR_GARRA, PUL_GARRA);
Forklift forklift(DIR_EMPILHADEIRA, PUL_EMPILHADEIRA);
MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor colorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
Ultrassonic frontalUltrassonic(TRIG_UlLTRASSONIC_FRONTAL,ECHO_UlLTRASSONIC_FRONTAL);
Ultrassonic lateralUltrassonic(TRIG_UlLTRASSONIC_LATERAL,ECHO_UlLTRASSONIC_LATERAL);
LightSensor rightIR(A0_DIREITA);
LightSensor leftIR(A0_ESQUERDA);
LightSensor LeftMiddleIR(A0_MEIO_ESQUERDA);
LightSensor RightMiddleIR(A0_MEIO_DIREITA);
LightSensor backIR(A0_TRAS);
LDR ldr(pinLDR);

Ultrassonic frontalUltrassonicSensor(echo_ultrassom_frontal, trig_ultrassom_frontal);
Ultrassonic lateralUltrassonicSensor(echo_ultrassom_lateral, trig_ultrassom_lateral);

// int ldr = A13;//Atribui A0 a variável ldr
// int valorldr = 0;//Declara a variável valorldr como inteiro

//LightSensor lateralRightIR(A0_DIREITA_LATERAL);
//LightSensor lateralLeftIR(A0_ESQUERDA_LATERAL);
Bumper bumper(BUMPER_PIN);



void TakeMemoryLeftMotor(){ // fica na main
  leftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  rightMotor.readEncoder();
}


void setup()
{
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING); // deixa na main
  // moveForSquare(3,&leftIR,&rightIR,&leftMotor,&rightMotor);
  // align(&LeftMiddleIR,&RightMiddleIR,&leftMotor,&rightMotor,70);
  beginning(&leftIR,&rightIR,&LeftMiddleIR, &RightMiddleIR, &backIR,&leftMotor,&rightMotor,&frontalUltrassonic,&lateralUltrassonic,&bumper,&ldr);
  // move_cm(5,FORWARD,&leftMotor,&rightMotor);
  // rotates(RIGHT,&leftMotor,&rightMotor);
  // pinMode(ldr, INPUT);//Define ldr (pino analógico A0) como saída
  

}
void loop(){
  // boucing(&leftMotor,&rightMotor,&leftIR,&rightIR,&bumper);
  // Serial.println(ldr.read());
  // Serial.println(frontalUltrassonic.distance_cm());
  // Serial.println(ldr.read());
  //  valorldr=analogRead(ldr);//Lê o valor do sensor ldr e armazena na variável valorldr
  //  Serial.print("Valor lido pelo LDR = ");//Imprime na serial a mensagem Valor lido pelo LDR
  //  Serial.println(valorldr);//Imprime na serial os dados de valorldr
  // Serial.println(frontalUltrassonicSensor.distance_cm());
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.print(" ");
  // Serial.println(middleIR.read());
  // // Serial.println(atrasIr.read());
  // Serial.println(middleIR.read());
  // Serial.println(frontalUltrassonic.distance_cm());
  // boucing(&leftMotor,&rightMotor,&leftIR,&leftIR,&bumper);
  // Serial.print(" LEFT  e RIGHT: ");
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.print(" bumper: ");
  // Serial.println(bumper.checkBumper());
  // rotates(LEFT,&leftMotor,&rightMotor);
  // delay(1000);
}

