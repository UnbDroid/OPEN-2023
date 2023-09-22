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

  // while (leftMotor.getEncoder() < 2048)
  // {
  //   leftMotor.moveForward(75);
  //   Serial.println(leftMotor.getEncoder());
  // }


//   while(micros()<1000000){
//     leftMotor.moveForward(255);
//     rightMotor.moveForward(255);
//   }
// stop(&leftMotor,&rightMotor);
// Serial.print(leftMotor.getEncoder());
// Serial.print(" ");
// Serial.println(rightMotor.getEncoder());

//  

// beginning(&leftIR,&rightIR,&leftMotor,&rightMotor,&frontalUltrassonic, &lateralUltrassonic,&colorSensor,&bumper);
// movePID(FORWARD,60,&leftMotor,&rightMotor);

// leftMotor.moveForward(255);
// rightMotor.moveForward(255);
//  Serial.println(checksUltrassonic(&frontalUltrassonic,&lateralUltrassonic, &leftMotor, &rightMotor));
 setPreviusTime(200000);
}


void loop(){
  
  movePID(FORWARD,0.5,&leftMotor,&rightMotor);
  // Serial.println(greenEdge(&leftMotor,&rightMotor,&leftIR,&rightIR));
  // delay(1000);
  
  
// Serial.print(leftIR.read());
// Serial.print(" ");
// Serial.println(rightIR.read());
  

  // Serial.println(lateralUltrassonic.distance_cm());
  // leftMotor.moveForward(100);
  // rightMotor.moveForward(100);
  // Serial.print(leftMotor.getEncoder());
  // Serial.print(" ");
  // Serial.println(rightMotor.getEncoder());
  
  // Serial.println(ultrassonic.distance_cm());
  // if(ultrassonic.distance_cm() < 10){
  //   stop(&leftMotor,&rightMotor);
  //   delay(100);
    
  // }
  // Serial.println(bumper.checkBumper());
  // colorSensor.read_values();
  // colorSensor.print_color_components_RGB();
  // colorSensor.identify_color();
    // movePID(FORWARD,255,&leftMotor,&rightMotor);
    // leftMotor.moveForward(255);
    // rightMotor.moveForward(255);
    // Serial.println("estou girando");
  // Serial.println("voltei pro começo");
  // leftMotor.moveForward(80);
  // rightMotor.moveForward(60);

  //   int encLeft = leftMotor.getEncoder();
  //   int encRight = rightMotor.getEncoder();

  //   if (!bumper.checkBumper()){
  //     stop(&leftMotor,&rightMotor);
  //   }
  //   if ((leftIR.read() > 200 && rightIR.read() < 200) || (leftIR.read() < 200 && rightIR.read() > 200)){
  //     stop(&leftMotor,&rightMotor);
  //     delay(500);

  //     encLeft = leftMotor.getEncoder() - encLeft;
  //     encRight = rightMotor.getEncoder() - encRight;
  //     // Serial.print(encLeft);
  //     // Serial.print(" ");
  //     // Serial.println(encRight);

  //     if (encLeft>0||encRight>0){
  //       resetEncoders(&leftMotor,&rightMotor);
        
  //       Serial.println("going backward");
  //       while (leftMotor.getEncoder() < encLeft && rightMotor.getEncoder() < encRight)
  //       {
  //         leftMotor.moveBackward(50);
  //         rightMotor.moveBackward(40);
  //       } 
  //       stop(&leftMotor,&rightMotor);
  //     }

  //     align(&leftIR,&rightIR,&leftMotor,&rightMotor,50);
  //     Serial.println("terminei de alinhar");
  //     stop(&leftMotor,&rightMotor);
      
  //     resetEncoders(&leftMotor,&rightMotor);
  //     while (leftMotor.getEncoder() < 341 && rightMotor.getEncoder() < 341)
  //     {
  //       // movePID(FORWARD,40,&leftMotor,&rightMotor);
  //       leftMotor.moveForward(55);
  //       rightMotor.moveForward(40);
  //       Serial.print("toquin p frente ");
  //       Serial.print(" ");
  //       Serial.print(leftMotor.getEncoder());
  //       Serial.print(" ");
  //       Serial.println(rightMotor.getEncoder());
  //     } 

  //     stop(&leftMotor,&rightMotor);
      
  //   }






// int leftWhite = 150;
// int rightWhite = 150;
// bool leftSeesBlack[2] = {false,false};
// bool rightSeesBlack[2] = {false,false};
// float valores[4];

// movePID(FORWARD,100,&leftMotor,&rightMotor);

// int readLeft = leftIR.read();
// int readRight = rightIR.read();
// valores[0] = readLeft;
// valores[2] = readRight;

// //identificar se tem algum no preto
// if ((readLeft > leftWhite && readRight < rightWhite) || (readLeft < leftWhite && readRight > rightWhite))
// {
//   if(readRight > rightWhite){
//     rightSeesBlack[0] = true;
//    }
//   if (readLeft > leftWhite){
//     leftSeesBlack[0] = true;
//   }

//   stop(&leftMotor,&rightMotor);
//   delay(1000);
  
//   readLeft = leftIR.read();
//   readRight = rightIR.read();
//   valores[1] = readLeft;
//   valores[3] = readRight;

//   if(readRight > rightWhite){
//     rightSeesBlack[1] = true;
//    }
//   if (readLeft > leftWhite){
//     leftSeesBlack[1] = true;
//   }


//   Serial.print(leftSeesBlack[0]);
//   Serial.print(leftSeesBlack[1]);
//   Serial.print(" ");
//   Serial.print(rightSeesBlack[0]);
//   Serial.print(rightSeesBlack[1]);
//   Serial.print(" ");
//   Serial.print(valores[0]);
//   Serial.print(" ");
//   Serial.print(valores[1]);
//   Serial.print(" ");
//   Serial.print(valores[2]);
//   Serial.print(" ");
//   Serial.print(valores[3]);
//   Serial.println();

  // int caso;
  // if(leftSeesBlack[1]){
  //   if(rightSeesBlack[1]){ 
  //     caso = 3;
  //   } else if (rightSeesBlack[0]){
  //     caso = 5;
  //   } else{
  //     caso = 1;
  //   }
  // } else{
  //   if(leftSeesBlack[0]){
  //     if(rightSeesBlack[1]) {
  //       caso = 4;
  //     }else{
  //       caso = 6;
  //     }
  //   } else if(rightSeesBlack[1]){
  //       caso = 2;
  //   } else{
  //     caso = 7;
  //   }
  // }
  // Serial.print("caso: ");
  // Serial.println(caso);
  
//   Serial.println("vou andar retooo");
//   int count = 0;
//   while (count < 1000)
//   {
//     movePID(FORWARD,50,&leftMotor,&rightMotor); 
//     count++; 
//   }
//   Serial.println("andei reto");
// }
}

