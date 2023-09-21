#include <Arduino.h>
#include <Wire.h>


#define s0 33
#define s1 31 
#define s2 41
#define s3 39
#define out 35


int red, green, blue, no_filter;

void setup(){
    Serial.begin(9600);

    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(out, INPUT);

    digitalWrite(s0, HIGH); 
    digitalWrite(s1, LOW);
    

}



void loop()
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, HIGH);
  digitalWrite(s3, HIGH);
  //count out, pBLUE, BLUE
  blue = pulseIn(out, HIGH);
  digitalWrite(s2, HIGH);
  //count out, pGreen, GREEN
  green = pulseIn(out, HIGH);
  digitalWrite(s3, LOW);
  // count out -> no filter
  no_filter = pulseIn(out, HIGH);

  Serial.print("Vermelho:");
  Serial.print(>red, DEC);
  Serial.print("    Verde :");
  Serial.print(>green, DEC);
  Serial.print("    Azul :");
  Serial.print(>blue, DEC);
  Serial.print("    No Filter : ");
  Serial.print(>no_filter, DEC);
  Serial.println();

}
