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


MotorDC::MotorDC(int pinoA, int pinoB, int pinoPwm){
    this->pinoA = pinoA;
    this->pinoB = pinoB;
    this->pinoPwm = pinoPwm;
    pinMode(this->pinoA, OUTPUT);
    pinMode(this->pinoB, OUTPUT);
    pinMode(this->pinoPwm, OUTPUT);

    pinMode(enca_right,INPUT);
    pinMode(encb_right,INPUT);
    pinMode(enca_left,INPUT);
    pinMode(encb_left,INPUT);

    /*
    AQUI É O CONSTRUTOR DA NOSSA CLASSE, JA ESTAMOS SETANDO O MODO DOS PINOS BEM AQUI.
    */
}

void MotorDC::andar_para_frente(int velocidade){
    digitalWrite(this->pinoA, HIGH);
    digitalWrite(this->pinoB, LOW);
    analogWrite(this->pinoPwm, velocidade);
}

void MotorDC::parar(){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, LOW);
}

void MotorDC::andar_para_tras(int velocidade){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, HIGH);
    analogWrite(this->pinoPwm, velocidade);
}


void MotorDC::readEncoder_right(){
  int b = digitalRead(enca_right);

  if (b>0){
    pos_encoder_right++;
  } else{
    pos_encoder_right--;
  }
}

void MotorDC::readEncoder_left(){
  int b = digitalRead(enca_left);

  if (b>0){
    pos_encoder_left++;
  } else{
    pos_encoder_left--;
  }
}

int MotorDC::getEncoderLeft(){
    return pos_encoder_left;
}

int MotorDC::getEncoderRight(){
    return pos_encoder_left;
}