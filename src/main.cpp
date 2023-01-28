#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>

#define s0 30
#define s1 28
#define s2 29
#define s3 26
#define out 27


//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;

ColorSensor frontalColorSensor(s0,s1,s2,s3,out);

void setup()
{

  Serial.begin(9600);
}



void loop()
{
 
  frontalColorSensor.identify_color();
  frontalColorSensor.print_color_components_RGB();
  delay(1000);
}