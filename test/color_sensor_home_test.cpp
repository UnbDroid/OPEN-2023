#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

// Arquivo para fazer os testes do sensor de cor isolado.



// Definição dos Pinos do Sensor de Cor Inferior Esquerdo
#define s0 30
#define s1 31
#define s2 46
#define s3 47
#define out 52

int color;
ColorSensor TestColorSensor(s0,s1,s2,s3,out);

// Serial.println(color);

void setup() {
  Serial.begin(9600);
  Serial.println("Testandoooo");
  // TestColorSensor.calibra_sensor();
  TestColorSensor.read_limit_values();

 
}

void loop(){
  // delay(1000);
  color = TestColorSensor.identify_color();
  // TestColorSensor.print_color_components_RGB();
}
