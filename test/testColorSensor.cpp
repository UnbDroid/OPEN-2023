#include <Arduino.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <MotorDC.h>
#include <Ultrassonic.h>


// Definição dos Pinos do Sensor de Cor Inferior Esquerdo
#define s0_left 33
#define s1_left 31
#define s2_left 27
#define s3_left 29
#define out_left 35

// Definição dos Pinos do Sensor de Cor Inferior Direito
#define s0_right 51
#define s1_right 53
#define s2_right 47
#define s3_right 50
#define out_right 49


// Definição dos Pinos do Sensor de Cor Frontal
#define s0_frontal 21
#define s1_frontal 20
#define s2_frontal 41
#define s3_frontal 39
#define out_frontal 37

#define S0_COLORSENSOR 33
#define S1_COLORSENSOR 31 
#define S2_COLORSENSOR 41
#define S3_COLORSENSOR 39
#define OUT_COLORSENSOR 35

ColorSensor frontalColorSensor(s0_frontal,s1_frontal,s2_frontal,s3_frontal,out_frontal);
ColorSensor leftColorSensor(s0_left,s1_left,s2_left,s3_left,out_left);
ColorSensor rightColorSensor(s0_right,s1_right,s2_right,s3_right,out_right);
ColorSensor CentralColorSensor(S0_COLORSENSOR, S1_COLORSENSOR, S2_COLORSENSOR, S3_COLORSENSOR, OUT_COLORSENSOR);


void setup(){
    Serial.begin(9600);
    leftColorSensor.calibra_sensor_inferior(0);  // Essa função serve para calibrar o sensor de cor inferior, se o sensor já estiver calibrado, comentar essa função.
    leftColorSensor.read_limit_values(0); // Essa função serve para ler os últimos valores calibrados pelo sensor de cor
    rightColorSensor.calibra_sensor_inferior(1);
    rightColorSensor.read_limit_values(1);
    frontalColorSensor.calibra_sensor_frontal(2); // Função feita para calibrar um sensor de cor frontal (Não deve ser usado no PELAS)
    frontalColorSensor.read_limit_values(2);

    Serial.println("Iniciando...");


}



void loop()
{
  delay(500);
  leftColorSensor.identify_color();
  rightColorSensor.identify_color();
  frontalColorSensor.identify_color();
  CentralColorSensor.

}
