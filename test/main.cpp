#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>


// Definição dos Pinos do Sensor de Cor Inferior Esquerdo
#define s0_left 33
#define s1_left 31
#define s2_left 27
#define s3_left 29
#define out_left 35


// Definição dos Pinos dos Motores
#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25


// Definição dos Pinos do Sensor de Cor Frontal
#define s0_frontal 21
#define s1_frontal 20
#define s2_frontal 41
#define s3_frontal 39
#define out_frontal 37


// PWM dos motores
#define PWM_Left 3
#define PWM_Right 2

// Parâmetros do Ultrassom
#define echoPin 43
#define trigPin 45

//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;

int velocidade = 50;
float distance;
int color = 100;


ColorSensor frontalColorSensor(s0_frontal,s1_frontal,s2_frontal,s3_frontal,out_frontal);
ColorSensor leftColorSensor(s0_left,s1_left,s2_left,s3_left,out_left);
MotorDC LeftMotor(IN1, IN3, PWM_Left);
MotorDC RightMotor(IN2, IN4, PWM_Right);

Ultrassonic ultrassound(echoPin,trigPin);


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
  // delay(500);

    // delay(100);


  delay(500);
  color = leftColorSensor.identify_color(2);
  leftColorSensor.print_color_components_RGB();
  if (color == 0){
    Serial.println("Viiii vermelhoooooo");
    velocidade = 0;
    LeftMotor.andar_para_frente(&velocidade);
    RightMotor.andar_para_frente(&velocidade);
    delay(5000); 
  }
  

  velocidade = 70;
  LeftMotor.andar_para_frente(&velocidade);
  RightMotor.andar_para_frente(&velocidade);
}

