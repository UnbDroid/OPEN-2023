#include <Arduino.h>
#include <Wire.h>

#define s0 30
#define s1 28
#define s2 29
#define s3 26
#define out 27


// //Pinos do led RGB
// int pinoledverm = 22;
// int pinoledverd = 23;
// int pinoledazul = 25;
 
//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;


void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(pinoledverm, OUTPUT);
  pinMode(pinoledverd, OUTPUT);
  pinMode(pinoledazul, OUTPUT);
  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}

void read_color() {
  //Rotina que le o valor das cores
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  this->red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  this->blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  this->green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, LOW);
  // cout OUT -> no filter
  this->no_filter = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void identify_color(){
  //Verifica se a cor vermelha foi detectada
  if ((28 < red && red < 70) && (105 < green && green < 170) && (80 < blue && blue < 130) && red < blue && red < green)
  {
    Serial.println("Vermelho");
    digitalWrite(pinoledverm, LOW); //Acende o led vermelho
    digitalWrite(pinoledverd, HIGH);
    digitalWrite(pinoledazul, HIGH);
  }
 
  //Verifica se a cor azul foi detectada
  else if ((100 < red && red < 170) && (70 < green && green < 160) && (50 <blue && blue < 120) && blue < red && blue < green)
  {
    Serial.println("Azul");
    digitalWrite(pinoledverm, HIGH);
    digitalWrite(pinoledverd, HIGH);
    digitalWrite(pinoledazul, LOW); //Acende o led azul
  }
 
  //Verifica se a cor verde foi detectada
  else if ((90 < red && red < 160) && (65 < green && green < 140) && (70 < blue && blue < 130) && green < red && green < blue )
  {
    Serial.println("Verde");
    digitalWrite(pinoledverm, HIGH);
    digitalWrite(pinoledverd, LOW); //Acende o led verde
    digitalWrite(pinoledazul, HIGH);
  }

    //Verifica se a cor amarela foi detectada
  else if ((10 < red && red < 60) && (30 < green && green < 90) && (45 < blue && blue < 100) && blue > red && blue > green)
  {
    Serial.println("Amarelo");
    digitalWrite(pinoledverm, LOW);
    digitalWrite(pinoledverd, LOW); //Acende o led amarelo
    digitalWrite(pinoledazul, HIGH);
  }

    //Verifica se a cor branca foi detectada
  else if ((0 < red && red < 70) && (0 < green && green < 70) && (0 < blue && blue < 70))
  {
    Serial.println("Branco");
    digitalWrite(pinoledverm, LOW);
    digitalWrite(pinoledverd, LOW); //Acende o led verde
    digitalWrite(pinoledazul, LOW);
  }

    //Verifica se a cor preta foi detectada
  else if ((110 < red && red < 180) && (110 < green && green < 220) && (110 < blue && blue < 190))
  {
    Serial.println("Preto");
    digitalWrite(pinoledverm, HIGH);
    digitalWrite(pinoledverd, HIGH); //Acende o led verde
    digitalWrite(pinoledazul, HIGH);
  }

  //else{}

  Serial.println();
}

void print_color_components_RGB(){

  //Mostra valores no serial monitor
  Serial.print("Vermelho:");
  Serial.print(red, DEC);
  Serial.print("    Verde :");
  Serial.print(green, DEC);
  Serial.print("    Azul :");
  Serial.print(blue, DEC);
  Serial.print("    No Filter : ");
  Serial.print(no_filter, DEC);
  Serial.println();

}
void loop()
{
  //Detecta a cor
  read_color();
  //Mostra valores no serial monitor
  //print_color_components_RGB();
  // Identifica a cor, printa o nome da cor e acende o LED da cor
  identify_color();
  delay(50);
  digitalWrite(pinoledverm, HIGH);
  digitalWrite(pinoledverd, HIGH);
  digitalWrite(pinoledazul, HIGH);
}