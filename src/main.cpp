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

int y=0;
int x =0;
int direcao=SOL::Norte; 
int destination[2];


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
  
  forklift.forklift_up_steps(0,2);
  Robot_Claw.close_claw_entirely();
  
  // delay(20000);
  // Robot_Claw.open_claw_with_cube();
  // forklift.forklift_down_steps(1,0);
  // delay(5000);
  // Robot_Claw.close_claw_with_cube();
  // forklift.forklift_up_steps(0,2);
  // delay(20000);
  // Robot_Claw.open_claw_with_cube();
  // forklift.forklift_down_steps(2,0);
  // delay(5000);
  // Robot_Claw.close_claw_with_cube();
  // forklift.forklift_up_steps(0,3);
  // delay(20000);
  // Robot_Claw.open_claw_with_cube();
  // forklift.forklift_down_steps(3,0);
  // delay(5000);
  // destination[0]=5;
  // destination[1]=5;
  //moveTo(&x,&y,destination,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&rightMiddleIR,&backIR,&leftMiddleIR);
  //stop(&leftMotor,&rightMotor);
  
  
  //rotates(LEFT,&leftMotor,&rightMotor);
  int position =0;
  //position = beginning(&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR,&backIR,&leftMotor,&rightMotor,&frontalUltrassonic,&lateralUltrassonic,&bumper,&ldr);
  // greenEdge(&leftMotor,&rightMotor,&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR,&ldr);
  
  if(position == 17){
     y = 1;
     x = 7;  
     direcao=SOL::Sul; 

   } else if (position == 67){
     y = 6;
     x = 7;  
     direcao=SOL::Norte; 

   } else if (position == 61){
     y = 6;
     x = 1;  
   direcao=SOL::Norte; 

   }else if (position == 11){
     y = 1;
     x = 1;  
     direcao=SOL::Sul; 
  }

  /*
  y = 5;
  x = 7;
  direcao = SOL::Sul;
  int *best = bestBlock(y,x);
  SOL::Direcao destinationDirection;
  Robot_Claw.open_claw_entirely();


  //moveTo(x,y,destination,direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&leftMiddleIR,&backIR,&rightMiddleIR);
  
  
  resetEncoders(&leftMotor,&rightMotor);

  while(backIR.read()<250){
    leftMotor.moveBackward(80);
    rightMotor.moveBackward(60);
  }
  stop(&leftMotor,&rightMotor);
  delay(500);
  if(x>4){
      Serial.println("aaaaaaaaaaaa");
      destinationDirection=SOL::Oeste;
      correctDirection(&direcao,destinationDirection,&leftMotor,&rightMotor);
  }
  else {
    Serial.println("abbbbbbbbbbbbbbbbbbbbbb");
      destinationDirection=SOL::Leste;
      correctDirection(&direcao,destinationDirection,&leftMotor,&rightMotor);
  }
  

  int typeOfBlock= pick_cube_from_right(&leftMotor,&rightMotor,&lateralUltrassonic,&frontalUltrassonic,&Robot_Claw,&forklift, &rightMiddleIR, &leftMiddleIR, &rightIR, &leftIR,&bumper);
  while(rightMiddleIR.read()<200&&leftMiddleIR.read() < 200){
      leftMotor.moveBackward(90);
      rightMotor.moveBackward(68);
  }
  stop(&leftMotor,&rightMotor);
  delay(500);
  align(&leftIR,&rightIR,&leftMotor,&rightMotor,80,&leftMiddleIR,&rightMiddleIR);
  stop(&leftMotor,&rightMotor);
  delay(500);
  while(rightMiddleIR.read()<150){
    leftMotor.moveBackward(90);
    rightMotor.moveBackward(68);
  }
  stop(&leftMotor,&rightMotor);
  delay(500);

  resetEncoders(&leftMotor,&rightMotor);

  if(y==5){
      direcao=SOL::Oeste;
      //direcaoDestino=SOL::Oeste;
      //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
      rotates(LEFT,&leftMotor,&rightMotor);
      x= 1; 
  }
  else{
      direcao=SOL::Leste;
      //direcaoDestino=SOL::Leste;
      rotates(LEFT,&leftMotor,&rightMotor);
      //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
      x=7;
  }

  stop(&leftMotor,&rightMotor);
  delay(500);
  while(!bumper.checkBumper()){
      boucing(&leftMotor,&rightMotor,&leftIR,&rightIR,&leftMiddleIR,&rightMiddleIR,&bumper);
  }
  stop(&leftMotor,&rightMotor);
  delay(500);
  align(&leftIR,&rightIR,&leftMotor,&rightMotor,70);
  stop(&leftMotor,&rightMotor);
  delay(500);
  */
         
}

void loop(){
  /*
  Serial.print(leftIR.read());
  Serial.print(" ");
  Serial.print(leftMiddleIR.read());
  Serial.print(" ");
  Serial.print(rightMiddleIR.read());
  Serial.print(" ");
  Serial.println(rightIR.read());
  */
  //stateMachine(&y,&x,&direcao,&leftIR,&rightIR,&leftMotor,&rightMotor,&Robot_Claw,&forklift,&lateralUltrassonicSensor,&frontalUltrassonicSensor,&rightMiddleIR,&backIR,&leftMiddleIR,&bumper);



  
  }