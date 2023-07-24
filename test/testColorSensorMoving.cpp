#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

#define s0 33
#define s1 31
#define s2 27
#define s3 29
#define out 35

#define IN1 22
#define IN2 24
#define IN3 23
#define IN4 25

#define PwM_left 3
#define PwM_right 2

#define echoPin 50
#define trigPin 51

//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;

int velocidade = 50;
float distance;
int color = 100;

// Ultrassonic ultrassound(echoPin,trigPin);

MotorDC leftMotor(IN1,IN2,PwM_left);
MotorDC rightMotor(IN3,IN4,PwM_right);
ColorSensor frontalColorSensor(s0,s1,s2,s3,out);

void setup(){
    Serial.begin(9600);
    // pinMode(IN1, OUTPUT);
    // pinMode(IN2, OUTPUT);
    // rightMotor.andar_para_frente(&velocidade);
    // leftMotor.andar_para_tras(&velocidade);
    // delay(3000)
}


void loop()
{
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);

    // distance = ultrassound.distance_meters();

    // Serial.println("a distance que o pulso volta e que ta lendo em metros é:");
    // Serial.println(distance);

    // delay(100);

  color = frontalColorSensor.identify_color();
  frontalColorSensor.print_color_components_RGB();
  if (color == 0){
    Serial.println("Viiii vermelhoooooo");
    velocidade = 0;
    leftMotor.andar_para_frente(&velocidade);
    rightMotor.andar_para_frente(&velocidade);
    delay(5000);
    
  }
  
  velocidade = 50;
  // delay(1000);
  leftMotor.andar_para_frente(&velocidade);
  rightMotor.andar_para_frente(&velocidade);
}
