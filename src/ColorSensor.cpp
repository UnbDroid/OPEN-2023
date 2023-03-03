#include<ColorSensor.h>
#include<Arduino.h>
#include<Wire.h>


int lim_inf_red_frontalsensor = 73;
int lim_sup_red_frontalsensor = 131;


ColorSensor::ColorSensor(int s0, int s1, int s2, int s3, int out){
    this->s0 = s0;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    this->out = out;
    pinMode(this->s0, OUTPUT);
    pinMode(this->s1, OUTPUT);
    pinMode(this->s2, OUTPUT);
    pinMode(this->s3, OUTPUT);
    pinMode(this->out, INPUT);

    digitalWrite(this->s0, HIGH);
    digitalWrite(this->s1, LOW);


}

void ColorSensor::read_values(){  //Rotina que lê as componentes RGB do sensor. Não é para ser chamada na main
  digitalWrite(this->s2, LOW);
  digitalWrite(this->s3, LOW);
  //count OUT, pRed, RED
  this->red = pulseIn(this->out, HIGH);
  digitalWrite(this->s3, HIGH);
  //count out, pBLUE, BLUE
  this->green = pulseIn(this->out, HIGH);
  digitalWrite(this->s2, HIGH);
  //count out, pGreen, GREEN
  this->blue = pulseIn(this->out, HIGH);
  digitalWrite(this->s3, LOW);
  // count out -> no filter
  this->no_filter = pulseIn(this->out, HIGH);
}





int ColorSensor::identify_color(int num){   // Lê os valores dos componentes RGB, identifica a cor e printa o nome da cor
  
  // num == 1 -> Frontal Sensor
  // num == 2 -> Left Sensor
  // num == 3 -> Right Sensor
  
  read_values();
  if (num == 1){ // Valores para o sensor frontal
  
    //Verifica se a cor vermelha foi detectada
    if ((73 < this->red && this->red < 131 ) && (158 < this->green && this->green < 222) && (190 < this->blue && this->blue < 247) && this->red < this->blue && this->red < this->green){
      Serial.println("Vermelho");
      return 0;}
  
    //Verifica se a cor azul foi detectada
    else if ((100 < this->red && this->red < 170) && (70 < this->green && this->green < 160) && (50 <this->blue && this->blue < 120) && this->blue < this->red && this->blue < this->green){
      Serial.println("Azul");
      return 1;}
  
    //Verifica se a cor verde foi detectada
    else if ((90 < this->red && this->red < 160) && (65 < this->green && this->green < 140) && (70 < this->blue && this->blue < 130) && this->green < this->red && this->green < this->blue ){
      Serial.println("Verde");
      return 2;}

      //Verifica se a cor amarela foi detectada
    else if ((10 < this->red && this->red < 60) && (30 < this->green && this->green < 90) && (45 < this->blue && this->blue < 100) && this->blue > this->red && this->blue > this->green){
      Serial.println("Amarelo");
      return 3;}

      //Verifica se a cor branca foi detectada
    else if ((0 < this->red && this->red < 70) && (0 < this->green && this->green < 70) && (0 < this->blue && this->blue < 70)){
      Serial.println("Branco");
      return 4;}

      //Verifica se a cor preta foi detectada
    else if ((110 < this->red && this->red < 180) && (110 < this->green && this->green < 220) && (110 < this->blue && this->blue < 190)){
      Serial.println("Preto");
      return 5;}

    else{
      Serial.println("Nenhuma Cor Identificada");
      return 6;
    }
  }
  else if (num == 2){
    //Verifica se a cor vermelha foi detectada
    if ((35 < this->red && this->red < 50 ) && (70 < this->green && this->green < 900) && (90 < this->blue && this->blue < 110) && this->red < this->blue && this->red < this->green){
      Serial.println("Vermelho");
      return 0;}
  
    //Verifica se a cor azul foi detectada
    else if ((100 < this->red && this->red < 170) && (70 < this->green && this->green < 160) && (50 <this->blue && this->blue < 120) && this->blue < this->red && this->blue < this->green){
      Serial.println("Azul");
      return 1;}
  
    //Verifica se a cor verde foi detectada
    else if ((90 < this->red && this->red < 160) && (65 < this->green && this->green < 140) && (70 < this->blue && this->blue < 130) && this->green < this->red && this->green < this->blue ){
      Serial.println("Verde");
      return 2;}

      //Verifica se a cor amarela foi detectada
    else if ((10 < this->red && this->red < 60) && (30 < this->green && this->green < 90) && (45 < this->blue && this->blue < 100) && this->blue > this->red && this->blue > this->green){
      Serial.println("Amarelo");
      return 3;}

      //Verifica se a cor branca foi detectada
    else if ((0 < this->red && this->red < 70) && (0 < this->green && this->green < 70) && (0 < this->blue && this->blue < 70)){
      Serial.println("Branco");
      return 4;}

      //Verifica se a cor preta foi detectada
    else if ((110 < this->red && this->red < 180) && (110 < this->green && this->green < 220) && (110 < this->blue && this->blue < 190)){
      Serial.println("Preto");
      return 5;}

    else{
      Serial.println("Nenhuma Cor Identificada");
      return 6;
    }
  }
  else
  {
    return 6;
  }

}




void ColorSensor::print_color_components_RGB(){

  //Mostra valores no serial monitor
  Serial.print("Vermelho:");
  Serial.print(this->red, DEC);
  Serial.print("    Verde :");
  Serial.print(this->green, DEC);
  Serial.print("    Azul :");
  Serial.print(this->blue, DEC);
  Serial.print("    No Filter : ");
  Serial.print(this->no_filter, DEC);
  Serial.println();

}
