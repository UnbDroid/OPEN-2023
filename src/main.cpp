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
LightSensor leftMiddleIR(A0_MEIO_ESQUERDA);
LightSensor digitalSensor(D0_DIGITAL);
LightSensor rightMiddleIR(A0_MEIO_DIREITA);
LightSensor backIR(A0_TRAS);
LDR ldr(pinLDR);

Ultrassonic frontalUltrassonicSensor(echo_ultrassom_frontal, trig_ultrassom_frontal);
Ultrassonic lateralUltrassonicSensor(echo_ultrassom_lateral, trig_ultrassom_lateral);

// int ldr = A13;//Atribui A0 a variável ldr
// int valorldr = 0;//Declara a variável valorldr como inteiro

//LightSensor lateralRightIR(A0_DIREITA_LATERAL);
//LightSensor lateralLeftIR(A0_ESQUERDA_LATERAL);
Bumper bumper(BUMPER_PIN);

// int x = 0;
// int y = 0;
// int direcao=SOL::Norte; 

void TakeMemoryLeftMotor(){ // fica na main
  leftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  rightMotor.readEncoder();
}

// void TakeMemoryRightMotor(){ // fica na main
//   rightMotor.readEncoder();
// }

void setup()
{

  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING); // deixa na main
  // forklift.forklift_up_steps(0,2);
  // int position = 
  // beginning(&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR,&backIR,&leftMotor,&rightMotor,&frontalUltrassonic,&lateralUltrassonic,&bumper,&ldr);
  // greenEdge(&leftMotor,&rightMotor,&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR,&ldr);
  //repositionBeginning(6, 1, 1,&leftMotor, &rightMotor, &leftIR, &rightIR, &leftMiddleIR,&rightMiddleIR,&backIR);

  // if(position == 17){
  //   y = 1;
  //   x = 7;  
  //   direcao=SOL::Sul; 

  // } else if (position == 67){
  //   y = 6;
  //   x = 7;  
  //   direcao=SOL::Norte; 

  // } else if (position == 61){
  //   y = 6;
  //   x = 1;  
  // direcao=SOL::Norte; 

  // }else if (position == 11){
  //   y = 1;
  //   x = 1;  
  //   direcao=SOL::Sul; 
  // }

  // Serial.print("posicao inicial: ");
  // Serial.print(y);
  // Serial.print(" ");
  // Serial.print(x);
  // Serial.print(" ");
  // Serial.println(direcao);


  int y=6;
  int x =1;
  int direcao=SOL::Oeste; 
  int destination[2];
  destination[0]=2;
  destination[1]=2;

  moveTo(&x,&y,destination,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&rightMiddleIR,&backIR,&leftMiddleIR);
  
  // while(!(backIR.read()>150)){ 
  //       leftMotor.moveBackward(80);
  //       rightMotor.moveBackward(60);
  //   }
  //   stop(&leftMotor,&rightMotor);
  //   delay(500);
  //   move_cm(128,&leftMotor,&rightMotor,&leftIR,&rightIR,&rightMiddleIR);
  //   stop(&leftMotor,&rightMotor);

}

void loop(){
  //Serial.println(rightMiddleIR.read());
  // Serial.println(frontalUltrassonic.distance_cm());
  // Serial.println(leftMiddleIR.read());
  
  // Serial.println(frontalUltrassonic.distance_cm());
  // Serial.println(ldr.read());
  // Serial.print("Bumper, ultra: ");
  // Serial.println(bumper.checkBumper());
  // Serial.print(" ");
  // Serial.println(frontalUltrassonic.distance_cm());

  // Serial.println(backIR.read());
  // leftMotor.moveForward(100);
  // rightMotor.moveForward(100);
  
//   Serial.print("D0: ");
//   Serial.print(analogRead(D0_DIGITAL));
// // Robot_Claw.close_claw_entirely();
// Serial.println(bumper.checkBumper());
// forklift.forklift_up_steps(0,2);
// forklift.forklift_down_steps(2,0);
  // leftMotor.moveForward(100);
  // rightMotor.moveForward(80);
  // Serial.print(" leitura IR: ");
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(leftMiddleIR.read());
  // Serial.print(" ");
  // Serial.print(rightMiddleIR.read());
  // Serial.print(" ");
  // Serial.println(rightIR.read());
  // forklift.forklift_up_steps(0,2);
  // Robot_Claw.close_claw_entirely();
  // forklift.forklift_up_steps(0,2);
  
}


  
  
 
  //forklift.forklift_up_steps(0,1);
  //pick_cube_from_right(&leftMotor, &rightMotor, &lateralUltrassonicSensor, &rightIR, &frontalUltrassonicSensor,&Robot_Claw, &forklift);
  //Robot_Claw.open_claw_with_cube();

  //boucing(&leftMotor,&rightMotor,&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR);

