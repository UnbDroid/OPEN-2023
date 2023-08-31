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
  // // align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);
  // rotates90(RIGHT,130,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);

  
  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.println();
  // align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);

    // movePID(FORWARD,40,&leftMotor,&rightMotor);
    // delay(4000);
    // stop(&leftMotor,&rightMotor);
}


void loop(){
  
  // // delay(1000);
  int branco_esq = 100;
  int branco_dir = 150;

  movePID(FORWARD,60,&leftMotor,&rightMotor);
   if ((leftIR.read() > branco_esq && rightIR.read() < branco_dir) || (leftIR.read() < branco_esq && rightIR.read() > branco_dir))
  {
    Serial.println("vendo trocado");
      Serial.print(leftIR.read());
      Serial.print(" ");
      Serial.print(rightIR.read());
      Serial.println();

    stop(&leftMotor,&rightMotor);
    align(&leftIR,&rightIR,&leftMotor,&rightMotor,40);
    movePID(FORWARD,40,&leftMotor,&rightMotor);
    Serial.println("vou andar agr?");
    delay(500);
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
  
  

}



// PRETO = 5#8

// threshold = 35 #50
// PROPORTIONAL_GAIN = 1.5

// #leitura_sensor = luzEsquerda.reflection()
// #print(leitura_sensor)
// leitura_sensor = getValorCorEsquerda()

// deviation =  threshold - leitura_sensor[0]
// turn_rate = PROPORTIONAL_GAIN * deviation
// rodas.drive(DRIVE_SPEED, turn_rate)




// Se ver preto com o esquerdo ou com o direito
//  parar
// se ver branco com esquerdo
//  anda com o esquerdo pra frente até ver preto 
// se ver branco com direito
//  anda com o direito pra frente até ver preto
// 
// 
