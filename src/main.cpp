#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>
#include <PID.h>

#define s0 33
#define s1 31
#define s2 27
#define s3 29
#define out 35

// #define IN1 22
// #define IN2 23
// #define IN3 24
// #define IN4 25

#define echoPin 45
#define trigPin 43

// #define PWM_Left 3
// #define PWM_Right 2

#define NMOTORS 2
const int enca[] = {2,19};
const int encb[] = {3,18};
const int pwm[] = {3,2};
const int in1[] = {22,23};
const int in2[] = {24,25};
//definir os pinos como listas e depois puxar isso no código, já que IN1 e IN3 são análogos, apenas de motores distintos
// MUITO BOM PRA VÁRIOS MOTORES!!

SimplePID pid[NMOTORS];
// Váriaveis globais
long prevT = 0;
volatile int posi[]= {0,0}; // uma lista com as posições dos encoders. Eu poderia facilmente definir esqPosi e dirPosi, mas vou deixar nesse estilo lista
// objetivo dos motores
float target_f[] = {0.0,0.0};
long target[] = {0,0};

void setup(){
  for(int k = 0; k < NMOTORS; k++){
      pinMode(enca[k],INPUT);
      pinMode(encb[k],INPUT);
      pinMode(pwm[k],OUTPUT);
      pinMode(in1[k],OUTPUT);
      pinMode(in2[k],OUTPUT);

      pid[k].setParameters(1,0,0,255);
  }
  
  attachInterrupt(digitalPinToInterrupt(enca[0]),readEncoder<0>, RISING);
  attachInterrupt(digitalPinToInterrupt(enca[1]),readEncoder<1>, RISING);

  Serial.println("target pos");

}

void loop() {

  long currT = micros();
  float deltaT = ((float)(currT-prevT)/(1.0e6));
  prevT = currT;

  // seta a posição objetivada
  setTarget(currT/1.0e6, deltaT);

  //mandar bala nos motores:
  for (int k = 0; k < NMOTORS; k++){
    int pwr,dir;
    // calcula os sinais PID pra cada motor:
    pid[k].evalu(posi[k],target[k],deltaT,pwr,dir);

    //envia tais sinais pros motores:
    setMotor(dir,pwr,pwm[k],in1[k],in2[k]);
  }
}



//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;
float dist = 0;

int velocidade = 70;
int color = 100;


Ultrassonic ultrassound(echoPin,trigPin);
ColorSensor frontalColorSensor(s0,s1,s2,s3,out);
MotorDC leftMotor(in1[0], in2[0], pwm[0]);
MotorDC rightMotor(in1[1], in2[1], pwm[1]);


void setup()
// {
//   Serial.begin(9600); 
// }

// void loop()
// {
//   // dist = ultrassound.distance_meters();
//   // Serial.println(dist);
//   // dist = ultrassound.distance_meters();
//   // Serial.println(dist);
//   // color = frontalColorSensor.identify_color();
//   // frontalColorSensor.print_color_components_RGB();

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

//   // color = frontalColorSensor.identify_color();
//   // frontalColorSensor.print_color_components_RGB();
//   // if (color == 0){
//   //   Serial.println("Viiii vermelhoooooo");
//   //   velocidade = 0;
//   //   leftMotor.andar_para_frente(&velocidade);
//   //   rightMotor.andar_para_frente(&velocidade);
//   //   delay(5000);
    
//   // }
  
//   // velocidade = 50;
//   // // delay(1000);
//   // leftMotor.andar_para_frente(&velocidade);
//   // rightMotor.andar_para_frente(&velocidade);
// }