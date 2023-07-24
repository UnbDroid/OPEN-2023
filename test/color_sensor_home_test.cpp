#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

// Arquivo para fazer os testes do sensor de cor isolado.



// Definição dos Pinos do Sensor de Cor - Teste em Casa
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
  // TestColorSensor.calibra_sensor(0);
  TestColorSensor.read_limit_values(0);

 
}

void loop(){
  // delay(500);
  color = TestColorSensor.identify_color2();
  // TestColorSensor.print_color_components_RGB();
}
