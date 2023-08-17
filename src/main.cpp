#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>

MotorDC LeftMotor(M_LEFT_LPWM, M_LEFT_RPWM,ENC_A_LEFT,ENC_B_LEFT);
MotorDC RightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM,ENC_A_RIGHT,ENC_B_RIGHT);

void TakeMemoryLeftMotor(){ // fica na main
  LeftMotor.readEncoder();
}

void TakeMemoryRightMotor(){ // fica na main
  RightMotor.readEncoder();
}

void setup()
{
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(ENC_B_RIGHT), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(ENC_B_LEFT),TakeMemoryLeftMotor, RISING); // deixa na main
  
  // movePID(FORWARD, 150 ,&LeftMotor, &RightMotor);
  // delay(700);
  // stop(&LeftMotor, &RightMotor);
  // // resetEncoders(&LeftMotor, &RightMotor);
  // movePID(BACKWARD, 150 ,&LeftMotor, &RightMotor);
  // delay(1000);
  // stop(&LeftMotor, &RightMotor);

  // LeftMotor.moveForward(150);
  // RightMotor.moveForward(150);
  // delay(700);
  // RightMotor.moveBackward(150);
  // LeftMotor.moveBackward(150);
  // delay(700);
  // stop(&LeftMotor, &RightMotor);
  

  // movePID(FORWARD, 150 ,&LeftMotor, &RightMotor);
  // delay(700);
  // stop(&LeftMotor, &RightMotor);
  // resetEncoders(&LeftMotor, &RightMotor);
  // movePID(BACKWARD, 150 ,&LeftMotor, &RightMotor);
  // delay(1000);
  


  // rotates90(RIGHT,150,&LeftMotor, &RightMotor);
  // delay(500);
  // rotates90(LEFT,150,&LeftMotor, &RightMotor);

//   LeftMotor.moveForward(150);
//   while (abs(LeftMotor.getEncoder() < 1100) && RightMotor.getEncoder() < 1100)
//   {
//     LeftMotor.moveForward(150);
//     RightMotor.moveBackward(150);
//   }
//   stop(&LeftMotor, &RightMotor);
  // delay(500);

  // LeftMotor.setEncoder(0);
  // RightMotor.setEncoder(0);

  // Serial.print(parametro_velocidade_esquerdo);
  // Serial.print(" ");
  // Serial.print(parametro_velocidade_direito);
  // Serial.println();
   

}

void loop(){

  // LeftMotor.setEncoder(0);
  // RightMotor.setEncoder(0);

  // int target = 1200;
  // int erro_left = 100;
  // int erro_right = 100;

  // while (erro_left > 10 && erro_right > 10)
  // {
  //   erro_left = abs(LeftMotor.getEncoder() - target);
  //   erro_right = abs(RightMotor.getEncoder() - target);
  //   int parametro_velocidade_esquerdo = KP*erro_left;
  //   int parametro_velocidade_direito = KP*erro_right;

  //   if (parametro_velocidade_direito > 255){
  //     parametro_velocidade_direito = 255;
  //   }
    
  //   if (parametro_velocidade_esquerdo > 255){
  //     parametro_velocidade_esquerdo = 255;
  //   }

  //   LeftMotor.moveForward(parametro_velocidade_esquerdo);
  //   RightMotor.moveBackward(parametro_velocidade_direito);

  //   if (parametro_velocidade_direito < 10){
  //       stop(&LeftMotor, &RightMotor);
  //   }
  // }
  
  LeftMotor.setEncoder(0);
  RightMotor.setEncoder(0);

  int erro_left = 100;
  int erro_right = 100;

  while (erro_left > 10 && erro_right > 10)
  {
    erro_left = abs(LeftMotor.getEncoder() - target);
    erro_right = abs(RightMotor.getEncoder() - target);
    int parametro_velocidade_esquerdo = KP*erro_left;
    int parametro_velocidade_direito = KP*erro_right;

    if (parametro_velocidade_direito > 255){
      parametro_velocidade_direito = 255;
    }
    
    if (parametro_velocidade_esquerdo > 255){
      parametro_velocidade_esquerdo = 255;
    }

    LeftMotor.moveBackward(parametro_velocidade_esquerdo);
    RightMotor.moveForward(parametro_velocidade_direito);

    if (parametro_velocidade_direito < 10){
        stop(&LeftMotor, &RightMotor);
    }
  }

  delay(500);
  
// // // Usando o serial, podemos ver o que os encoders estão retornando:
// Serial.print(LeftMotor.getEncoder());
// Serial.print(" ");
// Serial.print(RightMotor.getEncoder());
// Serial.println();


}
