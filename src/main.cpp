#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>
#include <Move.h>

#define s0 33
#define s1 31
#define s2 27
#define s3 29
#define out 35

#define IN1 22 
#define IN2 24 
#define IN3 25 
#define IN4 23

#define echoPin 45
#define trigPin 43

#define PWM_Left 4
#define PWM_Right 5

#define ENCA_Left 2
#define ENCB_Left 3
#define ENCA_Right 19
#define ENCB_Right 18


//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;
float dist = 0;
int velocidade = 255;
int color = 100;


// variaveis pro PID
int positionLeft= 0; // posição atual do encoder esquerdo
int positionRight = 0; // posição atual do encoder direito
int targetLeft = 100;
int targetRight = 100;
int pwrLeft = 0;
int pwrRight = 0;


Ultrassonic ultrassound(echoPin,trigPin);
ColorSensor frontalColorSensor(s0,s1,s2,s3,out);
MotorDC leftMotor(IN1, IN2, PWM_Left);
MotorDC rightMotor(IN4, IN3, PWM_Right);



void TakeMemoryLeftMotor(){ // fica na main
  LeftMotor.getEncoderLeft();
}

void TakeMemoryRightMotor(){ // fica na main
  RightMotor.getEncoderRight();
}



void setup()
{
  Serial.begin(9600); 
  // leftMotor.andar_para_frente(&velocidade);
  // rightMotor.andar_para_frente(&velocidade);
    
  attachInterrupt(digitalPinToInterrupt(encb_right), TakeMemoryRightMotor, RISING); //deixa na main
  attachInterrupt(digitalPinToInterrupt(encb_left),TakeMemoryLeftMotor, RISING); // deixa na main
}

void loop()
{
    
  moveForwardPid(&LeftMotor, &RightMotor,255);

  Serial.print(LeftMotor.getEncoderLeft());
  Serial.print(" ");
  Serial.print(RightMotor.getEncoderRight());
  Serial.println();
  
  // dist = ultrassound.distance_meters();
  // Serial.println(dist);
  // dist = ultrassound.distance_meters();
  // Serial.println(dist);
  // color = frontalColorSensor.identify_color();
  // frontalColorSensor.print_color_components_RGB();

//   if(ultrassound.distance_cm() < 10){
//     velocidade = 0;
//     leftMotor.andar_para_frente(&velocidade);
//     rightMotor.andar_para_frente(&velocidade);
//     delay(1000);
//  }
//   velocidade = 70;
//   delay(1000);
//   leftMotor.andar_para_frente(&velocidade);
//   rightMotor.andar_para_frente(&velocidade);

  // color = frontalColorSensor.identify_color();
  // frontalColorSensor.print_color_components_RGB();
  // if (color == 0){
  //   Serial.println("Viiii vermelhoooooo");
  //   velocidade = 0;
  //   leftMotor.andar_para_frente(&velocidade);
  //   rightMotor.andar_para_frente(&velocidade);
  //   delay(5000);
    
  // }
  
  // velocidade = 50;
  // // delay(1000);
  // leftMotor.andar_para_frente(&velocidade);
  // rightMotor.andar_para_frente(&velocidade);
}