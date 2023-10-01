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


Claw Robot_Claw(DIR_GARRA, PUL_GARRA);
Forklift forklift(DIR_EMPILHADEIRA, PUL_EMPILHADEIRA);
MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor colorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
Ultrassonic frontalUltrassonic(TRIG_UlLTRASSONIC_FRONTAL,ECHO_UlLTRASSONIC_FRONTAL);
Ultrassonic lateralUltrassonic(TRIG_UlLTRASSONIC_LATERAL,ECHO_UlLTRASSONIC_LATERAL);
LightSensor rightIR(A0_DIREITA);
LightSensor leftIR(A0_ESQUERDA);
LightSensor middleIR(A0_MEIO);

Ultrassonic frontalUltrassonicSensor(echo_ultrassom_frontal, trig_ultrassom_frontal);
Ultrassonic lateralUltrassonicSensor(echo_ultrassom_lateral, trig_ultrassom_lateral);

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
  beginning(&leftIR,&rightIR,&leftMotor,&rightMotor,&frontalUltrassonic,&lateralUltrassonic,&bumper);
  // align(&leftIR,&rightIR,&leftMotor,&rightMotor,80);
  // rotates(RIGHT,&leftMotor,&rightMotor);
}
int y=6;
int x =7;
int direcao=SOL::Norte;

void loop(){
  // Serial.println(frontalUltrassonic.distance_cm());
  // boucing(&leftMotor,&rightMotor,&leftIR,&leftIR);
  // Serial.print(" LEFT  e RIGHT: ");
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.println(rightIR.read());
  // Serial.println(bumper.checkBumper());
  // stateMachine(&y,&x,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&Robot_Claw,&forklift,&lateralUltrassonicSensor,&frontalUltrassonicSensor);
  //forklift.forklift_up_steps(0,1);
  //pick_cube_from_right(&leftMotor, &rightMotor, &lateralUltrassonicSensor, &rightIR, &frontalUltrassonicSensor,&Robot_Claw, &forklift);
  //Robot_Claw.open_claw_with_cube();

// int leftBlack = 100;
// int rightBlack = 100;

// if(leftIR.read()>leftBlack && leftIR.read()>rightBlack){
//   leftMotor.moveForward(130);
//   rightMotor.moveForward(100);
// }

// if (leftIR.read()<leftBlack) {
//     while(leftIR.read() < leftBlack){
//         leftMotor.moveForward(160);
//         rightMotor.moveBackward(60);
//     }
// }    
// else if (rightIR.read()<rightBlack) {
//     while(rightIR.read() < rightBlack){
//         rightMotor.moveForward(130);
//         leftMotor.moveBackward(80);
//     }
// } 
// }
}

