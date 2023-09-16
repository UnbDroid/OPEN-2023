#include <Arduino.h>
#include <Pins.h>
#include <MotorDC.h>
#include <Move.h>
#include <ColorSensor.h>
#include<LightSensor.h>
#include<Sol.h>
#include <PickCube.h>
#include <Ultrassonic.h>

MotorDC leftMotor(M_LEFT_LPWM, M_LEFT_RPWM, EN_LEFT_MOTOR, ENC_A_LEFT,ENC_B_LEFT);
MotorDC rightMotor(M_RIGHT_LPWM, M_RIGHT_RPWM, EN_RIGHT_MOTOR,ENC_A_RIGHT,ENC_B_RIGHT);
ColorSensor CentralColorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);
LightSensor rightIR(A0_DIREITA_FRENTE);
LightSensor leftIR(A0_ESQUERDA_FRENTE);
LightSensor lateral_leftIR(A0_LATERAL_LEFT);
LightSensor lateral_rightIR(A0_LATERAL_RIGHT);
Ultrassonic ultrassonicSensor(echo_ultrassom, trig_ultrassom);


int min_right_distance;
int right_distance;
int i;

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

  // for (i = 0; i < 30; i++){
  //   min_right_distance += lateral_rightIR.read();
  // }
  // Serial.println(min_right_distance);
  // // delay(10000);
  // min_right_distance /= 30;

  // rotates(LEFT, &leftMotor,&rightMotor);
  // rotates(RIGHT,&leftMotor,&rightMotor);
  // stop(&leftMotor,&rightMotor);
  // delay(2000);

  // Serial.print(leftIR.read());
  // Serial.print(" ");
  // Serial.print(rightIR.read());
  // Serial.println();

  // 
  
}


void loop(){
    pick_cube_from_right(&leftMotor,&rightMotor, &lateral_rightIR, &rightIR, &ultrassonicSensor);
    // Serial.println(UltrassonicSensor.distance_cm());
    // leftMotor.moveForward(75);
    // rightMotor.moveForward(55);
    // // movePID(FORWARD,30,&leftMotor,&rightMotor);
    // right_distance = rightIR.read();
    // Serial.println(right_distance);
    // Serial.print(" é maior que");
    // Serial.println(min_right_distance - 30);
    // if (right_distance < min_right_distance - 30){
    //   Serial.println("Simmm");
    //   stop(&leftMotor,&rightMotor);
    //   delay(2000);
    //   leftMotor.moveForward(85);
    //   rightMotor.moveForward(75);
    //   delay(500);
    //   stop(&leftMotor,&rightMotor);
    //   delay(2000);
    //   rotates(RIGHT, &leftMotor,&rightMotor);
    //   delay(2000);
    //   leftMotor.moveForward(75);
    //   rightMotor.moveForward(55);
    //   delay(2000);
    //   }

// int leftWhite = 200;
// int rightWhite = 200;
// int count = 0;

//   Serial.println("Teste 1:");
//   while(leftIR.read() < leftWhite || rightIR.read() < rightWhite){
//     movePID(FORWARD,75,&leftMotor,&rightMotor);
//   }
//   leftMotor.moveBackward(75);
//   rightMotor.moveBackward(75);
//   delay(500);
//   stop(&rightMotor,&leftMotor);

//   Serial.println("parei Teste 1");
//   delay(8000);

//   Serial.println("Teste 3:");
//   while(leftIR.read() < leftWhite || rightIR.read() < rightWhite){
//     movePID(FORWARD,75,&leftMotor,&rightMotor);
//   }
//   // resetEncoders()
//   for (int i = 75; i > count; i--)
//   {
//     movePID(BACKWARD,i,&leftMotor,&rightMotor);
//   }
//   stop(&rightMotor,&leftMotor);
//   Serial.println("parei Teste 3");
//   delay(5000);

  

// // bool leftSeesBlack[2] = {false,false};
// // bool rightSeesBlack[2] = {false,false};
// // float valores[4];

// movePID(FORWARD,100,&leftMotor,&rightMotor);

// int readLeft = leftIR.read();
// int readRight = rightIR.read();
// // valores[0] = readLeft;
// // valores[2] = readRight;

// //identificar se tem algum no preto
// if ((readLeft > leftWhite && readRight < rightWhite) || (readLeft < leftWhite && readRight > rightWhite))
// {
//   // if(readRight > rightWhite){
//   //   rightSeesBlack[0] = true;
//   //  }
//   // if (readLeft > leftWhite){
//   //   leftSeesBlack[0] = true;
//   // }

//   stop(&leftMotor,&rightMotor);
//   delay(1000);
  
//   int a = 0;
//    while (a < 80)
//   {
//     movePID(BACKWARD,50,&leftMotor,&rightMotor); 
//     a++; 
//   }
  
  
//   // readLeft = leftIR.read();
//   // readRight = rightIR.read();
//   // valores[1] = readLeft;
//   // valores[3] = readRight;

//   // if(readRight > rightWhite){
//   //   rightSeesBlack[1] = true;
//   //  }
//   // if (readLeft > leftWhite){
//   //   leftSeesBlack[1] = true;
//   // }


//   // Serial.print(leftSeesBlack[0]);
//   // Serial.print(leftSeesBlack[1]);
//   // Serial.print(" ");
//   // Serial.print(rightSeesBlack[0]);
//   // Serial.print(rightSeesBlack[1]);
//   // Serial.print(" ");
//   // Serial.print(valores[0]);
//   // Serial.print(" ");
//   // Serial.print(valores[1]);
//   // Serial.print(" ");
//   // Serial.print(valores[2]);
//   // Serial.print(" ");
//   // Serial.print(valores[3]);
//   // Serial.println();

//   // int caso;
//   // if(leftSeesBlack[1]){
//   //   if(rightSeesBlack[1]){ 
//   //     caso = 3;
//   //   } else if (rightSeesBlack[0]){
//   //     caso = 5;
//   //   } else{
//   //     caso = 1;
//   //   }
//   // } else{
//   //   if(leftSeesBlack[0]){
//   //     if(rightSeesBlack[1]) {
//   //       caso = 4;
//   //     }else{
//   //       caso = 6;
//   //     }
//   //   } else if(rightSeesBlack[1]){
//   //       caso = 2;
//   //   } else{
//   //     caso = 7;
//   //   }
//   // }
//   // Serial.print("caso: ");
//   // Serial.println(caso);
    
  
//   align(&leftIR,&rightIR,&leftMotor,&rightMotor,55);
  
//   Serial.println("vou andar retooo");
//   int count = 0;
//   while (count < 1000)
//   {
//     movePID(FORWARD,50,&leftMotor,&rightMotor); 
//     count++; 
//   }
//   Serial.println("andei reto");

//   }
//   Serial.print(leftIR.read());
//   Serial.print(" ");
//   Serial.print(rightIR.read());
//   Serial.println();
}



// //desenvolver alguma lógica com relação à quem chega aqui
//   resetEncoders(&leftMotor,&rightMotor);
  
  // pos_atual_dir = fabs(rightMotor.getEncoder() - pos_atual_dir);
  // pos_atual_esq = fabs(leftMotor.getEncoder()- pos_atual_esq);
