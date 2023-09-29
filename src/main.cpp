#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Ultrassonic.h>
#include<Sol.h>
#include <Bumper.h>





MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor colorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
Ultrassonic frontalUltrassonic(TRIG_UlLTRASSONIC_FRONTAL,ECHO_UlLTRASSONIC_FRONTAL);
Ultrassonic lateralUltrassonic(TRIG_UlLTRASSONIC_LATERAL,ECHO_UlLTRASSONIC_LATERAL);
LightSensor rightIR(A0_DIREITA_FRENTE);
LightSensor leftIR(A0_ESQUERDA_FRENTE);
LightSensor lateralRightIR(A0_DIREITA_LATERAL);
LightSensor lateralLeftIR(A0_ESQUERDA_LATERAL);
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

  // colorSensor.calibra_sensor_inferior(0);  // Essa função serve para calibrar o sensor de cor inferior, se o sensor já estiver calibrado, comentar essa função.
  colorSensor.read_limit_values(0); // Essa função serve para ler os últimos valores calibrados pelo sensor de cor

// Serial.println("Iniciando...");

//   // while(micros()<1000000){
// //     leftMotor.moveForward(255);
// //     rightMotor.moveForward(255);
// //     delay(1000);
// //   // }
// // stop(&leftMotor,&rightMotor);
// Serial.print("Esq: ");
// Serial.println(leftMotor.getEncoder());
// // Serial.print(" ");
// Serial.print("Dir: ");
// Serial.println(rightMotor.getEncoder());

// calibrateMotorsCT(&leftMotor,&rightMotor);
// align(&leftIR,&rightIR,&leftMotor,&rightMotor,100);
// while(leftIR.read()<110 && rightIR.read()<110){
//   leftMotor.moveForward(100);
//   rightMotor.moveForward(80);
//   Serial.println("to andando");
// } 
// stop(&leftMotor,&rightMotor);
// delay(1000);
// align(&leftIR,&rightIR,&leftMotor,&rightMotor,80);
// Serial.println("terminei de alinhar");

//beginning(&leftIR,&rightIR,&leftMotor,&rightMotor,&frontalUltrassonic, &lateralUltrassonic,&colorSensor,&bumper);
// move_cm(30,FORWARD,&leftMotor,&rightMotor);
// rotates(RIGHT,&leftMotor,&rightMotor);
// stop(&leftMotor,&rightMotor);
// leftMotor.moveForward(80);
// rightMotor.moveForward(60);
// while(micros() < 20000000){

  // movePID(FORWARD,0.5,&leftMotor,&rightMotor);
// }
// delay(500);
// Serial.println("giro: ");
// rotates(RIGHT,&leftMotor,&rightMotor);
// delay(500);

// rotates(RIGHT,&leftMotor,&rightMotor);
// stop(&leftMotor,&rightMotor);
// delay(500);

//   setPreviusTime(micros());
//   while(!(rightIR.read()>110&&leftIR.read()>110)){
//     movePID(FORWARD,0.5,&leftMotor,&rightMotor);
//   } 

//   stop(&leftMotor,&rightMotor);
//   delay(500);
//   align(&leftIR,&rightIR,&leftMotor,&rightMotor,100);


}


void loop(){

boucing(&leftMotor,&rightMotor, &leftIR, &rightIR);
//   Serial.print(leftIR.read());
//   Serial.print(" ");
//   Serial.println(rightIR.read());

// if ((leftIR.read()<80 && rightIR.read()<300) || (leftIR.read()>80 && rightIR.read()>300)){ // esq e dir no branco ou os dois no preto
//   Serial.println("os dois =");
//   leftMotor.moveForward(80);
//   rightMotor.moveForward(60);
// }

// if(leftIR.read()>80 && rightIR.read() < 300){ //esq no preto e dir no branco
//   Serial.println("ESQ preto");
//   while(leftIR.read()>80){
//     leftMotor.moveForward(130);
//   }
//   stop(&leftMotor,&rightMotor);

// } else if(rightIR.read()>300 && leftIR.read()<80) { // esq no branco e dir no preto
//   Serial.println("DIR preto");
//   while(rightIR.read()>300){
//     rightMotor.moveForward(100);
//   }
//   stop(&leftMotor,&rightMotor);
// } 



  

  
  // delay(100);
  // movePID_cm(30,FORWARD,0.5,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);
  // delay(1000);
  // Serial.println(rightIR.read());



   // movePID_cm(30,FORWARD,0.5,&leftMotor,&rightMotor);
  // Serial.println(bumper.checkBumper());
  // rotates(RIGHT,&leftMotor,&rightMotor);
  // delay(1000);
  // // Serial.println(leftIR.read());
  // movePID(FORWARD,0.5,&leftMotor,&rightMotor);
  // leftMotor.moveForward(255);
  // Serial.println(leftMotor.getEncoder());
}

