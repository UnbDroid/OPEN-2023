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

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

#define echoPin 45
#define trigPin 43

#define PWM_Left 3
#define PWM_Right 2

#define ENCA_Left 2
#define ENCB_Left 3
#define ENCA_Right 19
#define ENCB_Right 18

#define KP_Left 1
#define KP_Right 1
#define KD_Left 0
#define KD_Right 0
#define KI_Left 0
#define KI_Right 0
#define UMAX 255
#define UMIN 0


//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;
float dist = 0;
int velocidade = 70;
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

// instanciando o PID de cada motor
SimplePID pidLeft(KP_Left,KD_Left,UMAX,UMIN,ENCA_Left,ENCB_Left);
SimplePID pidRight(KP_Right,KD_Right,UMAX,UMIN,ENCB_Right,ENCB_Right);

// Váriaveis globais
long previousTime = 0;

void readEncoderLeft(){
  pidLeft.readEncoder(ENCB_Left,positionLeft);
}
void readEncoderRight(){
  pidRight.readEncoder(ENCB_Right,positionRight);

}

void setup(){
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENCA_Left),readEncoderLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA_Right),readEncoderRight, RISING);

}

void loop() {
  long currentTime = micros();
  float deltaT = ((float)(currentTime-previousTime)/(1.0e6)); // divide por 10e6 paa converter de microsec para sec. Esse deltaT vai ser usado no detivativo/integrativo
  previousTime = currentTime;

  // aqui devemos puxar a função que calcula a potencia dos motores e de fato enviá-la, porém não consegui finalizar isso.
  // ControlValue retorna uma soma de PID que deve ser enviada para outra função, setMotorsPID, que de fato indica a potência dos motores e a direção que devem girar
  // Começamos chamando essas:
  // pidLeft.controlValue(positionLeft, targetLeft, deltaT,pwrLeft, KP_Left,KD_Left,KI_Left); 
  // pidRight.controlValue(positionRight, targetRight, deltaT,pwrRight,KP_Right,KD_Right,KI_Right);
  

  }

//-------------------------------------




// void setup()
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