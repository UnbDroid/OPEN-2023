#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>

MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor CentralColorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
LightSensor rightIR(A0_DIREITA_FRENTE);
LightSensor leftIR(A0_ESQUERDA_FRENTE);

//in3
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
  // rotates90(RIGHT,130,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);
  // delay(1000);
  // rotates90(LEFT,130,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);
  // delay(1000);
  
  // while (leftIR.read()<200 && rightIR.read()<200){
  // leftMotor.moveForward(40);
  // rightMotor.moveForward(40);
  // }
  // stop(&leftMotor,&rightMotor);
  // delay(1000);
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.println();
  // align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);
  // rotates(AROUND,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);
    // align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);

  
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.println();

    // movePID(FORWARD,40,&leftMotor,&rightMotor);
    // delay(4000);
    // stop(&leftMotor,&rightMotor);
    // Serial.println("rodando");
}


void loop(){
  
  // delay(1000);
  int branco_esq = 200 ;
  int branco_dir = 200;

  movePID(FORWARD,70,&leftMotor,&rightMotor);
   if ((leftIR.read() > branco_esq && rightIR.read() < branco_dir) || (leftIR.read() < branco_esq && rightIR.read() > branco_dir))
  {
    stop(&leftMotor,&rightMotor);
    Serial.println("vendo trocado");
    Serial.print(leftIR.read());
    Serial.print(" ");
    Serial.print(rightIR.read());
    Serial.println();

    movePID(BACKWARD,45,&leftMotor,&rightMotor);
    delay(500);
    stop(&leftMotor,&rightMotor);
    delay(1000);
    
    align(&leftIR,&rightIR,&leftMotor,&rightMotor,45);
    movePID(FORWARD,50,&leftMotor,&rightMotor);
    delay(1500);
    // while (leftIR.read() > branco_esq || rightIR.read() > branco_dir)
    // {
    //   movePID(FORWARD,50,&leftMotor,&rightMotor);
    //   Serial.println("andei ");
    //   Serial.print(leftIR.read());
    //   Serial.print(" ");
    //   Serial.print(rightIR.read());
    //   Serial.println();
    // }
    
    // movePID(FORWARD,45,&leftMotor,&rightMotor);
    // Serial.println("vou andar agr?");
    // leftMotor.moveForward(50);
    // rightMotor.moveForward(50);
    // delay(1000);
    // Serial.println("andei");
  }
}





  // } else if(leftIR.read() < branco && rightIR.read() > branco) {

  //   Serial.println("DIR no preto");
  //   Serial.print(leftIR.read());
  //   Serial.print(" ");
  //   Serial.print(rightIR.read());
  //   Serial.println();

  //   stop(&leftMotor,&rightMotor);
  //   align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);


  // }
  
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.println();


  // int goal = 300;
  // int leitura_dir = rightIR.read();
  // int delta = goal-leitura_dir;
  // int erro = delta*0.1;
  // Serial.println(leitura_dir);
  
  // if(delta>0){
  //   leftMotor.moveForward(erro);
  // } else {
  //   rightMotor.moveForward(erro);
  // }

