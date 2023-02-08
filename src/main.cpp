#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>

#define s0 33
#define s1 31
#define s2 27
#define s3 29
#define out 35

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

#define PWM_Left 3
#define PWM_Right 2


//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;

int velocidade = 50;
int color = 100;

ColorSensor frontalColorSensor(s0,s1,s2,s3,out);
MotorDC LeftMotor(IN1, IN3, PWM_Left);
MotorDC RightMotor(IN2, IN4, PWM_Right);


void setup()
{

  Serial.begin(9600);
}



void loop()
{
 
  color = frontalColorSensor.identify_color();
  frontalColorSensor.print_color_components_RGB();
  if (color == 0){
    Serial.println("Viiii vermelhoooooo");
    velocidade = 0;
    LeftMotor.andar_para_frente(&velocidade);
    RightMotor.andar_para_frente(&velocidade);
    delay(5000);
    
  }
  
  velocidade = 50;
  // delay(1000);
  LeftMotor.andar_para_frente(&velocidade);
  RightMotor.andar_para_frente(&velocidade);
}