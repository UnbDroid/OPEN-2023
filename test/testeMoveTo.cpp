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
LightSensor sensorDireita(A0_DIREITA_FRENTE);
LightSensor sensorEsquerda(A0_ESQUERDA_FRENTE);

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
  // rotates90(RIGHT,100,&leftMotor,&rightMotor);
  //rotates90(RIGHT,160,&leftMotor,&rightMotor);
  // CentralColorSensor.calibra_sensor_inferior(0);  // Essa função serve para calibrar o sensor de cor inferior, se o sensor já estiver calibrado, comentar essa função.
  // CentralColorSensor.read_limit_values(0); // Essa função serve para ler os últimos valores calibrados pelo sensor de cor
  // pinMode(EN_LEFT_MOTOR, OUTPUT);
  // pinMode(M_LEFT_RPWM,OUTPUT);
  // pinMode(M_LEFT_LPWM,OUTPUT);

  // pinMode(EN_RIGHT_MOTOR, OUTPUT);
  // pinMode(M_RIGHT_RPWM,OUTPUT);
  // pinMode(M_RIGHT_LPWM,OUTPUT);

  // digitalWrite(M_RIGHT_RPWM, HIGH);
  // digitalWrite(M_RIGHT_LPWM,LOW);
  // analogWrite(EN_RIGHT_MOTOR, 130);
  
  
  // int count = 150;
  // for (int i = 30; i < count; i++)
  // {
  //   movePID(FORWARD,i,&LeftMotor,&RightMotor);  
  //   delay(100);
  //   Serial.println(i);
  // }
  
  // movePID(FORWARD,128,&LeftMotor,&RightMotor);
  // LeftMotor.moveForward(255);
  // RightMotor.moveForward(255);
  // delay(1000);
  // stop(&LeftMotor,&RightMotor);
  // delay(1400);
  // stop(&LeftMotor,&RightMotor);
  // delay(1000);
  
  // delay(1000);
  // while (analogRead(A0_DIREITA_FRENTE) < 40 && analogRead(A0_ESQUERDA_FRENTE) < 40)
  // {
  //   movePID(FORWARD,70,&LeftMotor,&RightMotor); 
  // }
  // stop(&LeftMotor,&RightMotor);
  // movePID(FORWARD,80,&LeftMotor,&RightMotor);
  // delay(4000);
  // int count = 200;
  // for (int i = 130; i < count; i++)
  // {
  //   movePID(FORWARD,i,&LeftMotor,&RightMotor); 
  //   delay(50);
  // }
  
  
  


} 

int a = Directions::BACKWARD;
int dir = 2;
int y = 6;
int x =7;
int direcaoAtual = SOL::Oeste;
int direcaoDestino = SOL::Sul;

void loop(){
  // static int flag =0;  
    // corrigirDirecao3()
  // if(flag ==0){
  //   moveForSquare(2,&sensorEsquerda,&sensorDireita,&leftMotor,&rightMotor);
  //   flag++;
  //   stop(&leftMotor,&rightMotor);
  // }
  
  
  maquinaDeEstados(&y,&x,&direcaoAtual,&sensorEsquerda,&sensorDireita,&leftMotor,&rightMotor);
  
  //  stop(&leftMotor,&rightMotor);
//      while(direcaoAtual!=direcaoDestino){
//      corrigirDirecao(&direcaoAtual,&leftMotor,&rightMotor);    //stop(&leftMotor,&rightMotor);
//    }
//    stop(&leftMotor,&rightMotor);
  // Serial.print("Direita: ");
  // Serial.print(sensorDireita.read());
  // Serial.print(" ");
  // Serial.print("Esquerda: ");
  // Serial.println(sensorEsquerda.read());
  
  // if(flag<1){
    
    ;
  // }
  
  // movePID(FORWARD,160,&leftMotor,&rightMotor);
//   alinhar(&leftMotor,&rightMotor,&sensorDireita,&sensorEsquerda);
  // while(direcaoAtual!=direcaoDestino){ 
  //   corrigirDirecao(&direcaoAtual,&leftMotor,&rightMotor);
  // }
  // if (analogRead(A0_DIREITA_FRENTE) > 60 || analogRead(A0_ESQUERDA_FRENTE) > 60){
  //   stop(&leftMotor, &rightMotor);
  //   leftMotor.moveForward(1000);
  //   delay(3000);
  //   stop(&leftMotor, &rightMotor);
  // }
  // rotates90(RIGHT, 130, &LeftMotor, &RightMotor);
  // rotates90(RIGHT, 130, &LeftMotor, &RightMotor);
  // stop(&LeftMotor,&RightMotor);
  // delay(1000);
  // Serial.print(analogRead(A0_DIREITA_FRENTE));
  // Serial.print(" ");
  // Serial.print(analogRead(A0_ESQUERDA_FRENTE));
  // Serial.println();
  // // // Usando o serial, podemos ver o que os encoders estão retornando:
  // Serial.print(leftMotor.getEncoder());
  // Serial.print(" ");
  // Serial.print(rightMotor.getEncoder());
  // Serial.println();
  //CentralColorSensor.read_values();
  //CentralColorSensor.print_color_components_RGB();
}

