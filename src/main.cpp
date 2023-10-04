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
LightSensor backIR(A0_TRAS);

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
  //moveForSquare(5,&leftIR,&rightIR,&leftMotor,&rightMotor,&middleIR);

  // beginning(&leftIR,&rightIR,&leftMotor,&rightMotor,&frontalUltrassonic,&lateralUltrassonic,&bumper);
  //rotates(RIGHT,&leftMotor,&rightMotor);


  // colorSensor.calibra_sensor_inferior(0);  // Essa função serve para calibrar o sensor de cor inferior, se o sensor já estiver calibrado, comentar essa função.
  //colorSensor.read_limit_values(0); // Essa função serve para ler os últimos valores calibrados pelo sensor de cor
  /*
  
  
  testeMove(5,&leftIR,&rightIR,&leftMotor,&rightMotor,&middleIR);
  resetEncoders(&leftMotor,&rightMotor);
  while(rightMotor.getEncoder()<=150||leftMotor.getEncoder()<=150){
        leftMotor.moveBackward(100);
        rightMotor.moveBackward(80);
    }
  stop(&leftMotor,&rightMotor);
  */

  int y=2;
  int x =6;
  int direcao=SOL::Norte; 
  int destination[2];
  destination[0]=6;
  destination[1]=3;
  moveTo(&x,&y,destination,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&middleIR,&backIR);
  destination[0]=5;
  destination[1]=3;
  moveTo(&x,&y,destination,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&middleIR,&backIR);
  destination[0]=2;
  destination[1]=6;
  moveTo(&x,&y,destination,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&middleIR,&backIR);
}
  


void loop(){

  // stateMachine(&y,&x,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&Robot_Claw,&forklift,&lateralUltrassonicSensor,&frontalUltrassonicSensor);
  //forklift.forklift_up_steps(0,1);
  //pick_cube_from_right(&leftMotor, &rightMotor, &lateralUltrassonicSensor, &rightIR, &frontalUltrassonicSensor,&Robot_Claw, &forklift);
  //Robot_Claw.open_claw_with_cube();
  //Serial.print("IR meio ");
  //Serial.println(backIR.read());
}

