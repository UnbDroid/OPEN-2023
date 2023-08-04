#include<MotorDC.h>
#include<Arduino.h>
#include<Wire.h>
/*
AQUI O QUE QUE ACONTECE? BOM BASICAMENTE SE LEMBRAM QUANDO A GENTE PEGA UMA STRING POR EXEMPLO
E FAZIA STRING.LENGTH, ETC? ESSE '.' SÃO MÉTODOS E QUE A GENTE IMPLEMENTA DESSE JEITO
COLOCANDO A CLASSE::( MÉTODO OU ATRIBUTO)
ESTOU PASSANDO UM PONTEIRO PARA A FUNÇÃO DE ANDAR PORQUE PRECISAREMOS PASSAR UM PONTEIRO 
PARA FAZER O CONTROLE, CASO NÃO SAIBAM O QUE É, POSSO TENTAR EXPLICAR COMO FUNCIONA

*/


MotorDC::MotorDC(int pinoA, int pinoB, int pinoPwm, int pinEncA, int pinEncB){
    this->pinoA = pinoA;
    this->pinoB = pinoB;
    this->pinoPwm = pinoPwm;
    pinMode(this->pinoA, OUTPUT);
    pinMode(this->pinoB, OUTPUT);
    pinMode(this->pinoPwm, OUTPUT);
    pinMode(this->pinEncA, INPUT);
    pinMode(this->pinEncB, INPUT);

    /*
    AQUI É O CONSTRUTOR DA NOSSA CLASSE, JA ESTAMOS SETANDO O MODO DOS PINOS BEM AQUI.
    */
}
MotorDC::MotorDC(int RPWM,int LPWM, int pinEncA,int pinEncB){
  this->pinoA=RPWM;
  this->pinoB= LPWM;
  this->encA=pinEncA;
  this->encB=pinEncB;
}
void MotorDC::moveForward(int velocidade){
    analogWrite(this->pinoA, 0);
    analogWrite(this->pinoB, velocidade);
}

void MotorDC::stop(){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, LOW);
}

void MotorDC::moveBackward(int velocidade){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, HIGH);
    analogWrite(this->pinoPwm, velocidade);
}


void MotorDC::readEncoder(){
  int b = digitalRead(encA);

  if (b>0){
    posEncoder++;
  } else{
    posEncoder--;
  }
}

int MotorDC::getEncoder(){
    return posEncoder;
}

// int MotorDC::getEncoderRight(){
//     return pos_encoder_left;
// }