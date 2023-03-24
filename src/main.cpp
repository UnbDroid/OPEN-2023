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



// Definição dos Pinos dos Motores
#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25



// Definição dos Pinos do Sensor de Cor - Teste em Casa
#define s0_home 30
#define s1_home 31
#define s2_home 46
#define s3_home 47
#define out_home 52


// Definição dos Pinos do Sensor de Cor Frontal
#define s0_frontal 21
#define s1_frontal 20
#define s2_frontal 41
#define s3_frontal 39
#define out_frontal 37


// PWM dos motores
#define PWM_Left 1
#define PWM_Right 0

// Parâmetros do Ultrassom Frontal
#define echoPin_frontal 43
#define trigPin_frontal 45

// Parâmetros do Ultrassom Lateral Esquerdo
#define echoPin_left 42
#define trigPin_left 44


//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int no_filter = 0;

int velocidade = 50;
float frontal_distance;
float left_distance;
int color = 100;


ColorSensor frontalColorSensor(s0_frontal,s1_frontal,s2_frontal,s3_frontal,out_frontal);
ColorSensor leftColorSensor(s0_left,s1_left,s2_left,s3_left,out_left);
ColorSensor rightColorSensor(s0_right,s1_right,s2_right,s3_right,out_right);
ColorSensor homeColorSensor(s0_home,s1_home,s2_home,s3_home,out_home);
MotorDC LeftMotor(IN1, IN3, PWM_Left);
MotorDC RightMotor(IN2, IN4, PWM_Right);
Ultrassonic frontalUltrassonic(echoPin_frontal, trigPin_frontal);
Ultrassonic leftUltrassonic(echoPin_left, trigPin_left);




void setup(){
    Serial.begin(9600);
    // leftColorSensor.calibra_sensor(0);
    // leftColorSensor.read_limit_values(1);
    // rightColorSensor.calibra_sensor_inferior(2);
    // rightColorSensor.read_limit_values(2);
    // frontalColorSensor.calibra_sensor(0);
    // frontalColorSensor.read_limit_values(0);
    // homeColorSensor.calibra_sensor_inferior(3);
    homeColorSensor.read_limit_values(3);
    Serial.println("Iniciando...");

}



void loop()
{
  // delay(500);
  homeColorSensor.identify_color3();
  // homeColorSensor.print_color_components_RGB();

  // frontal_distance = leftUltrassonic.distance_cm();
  // Serial.println(frontal_distance);
  // if (frontal_distance < 100){
  //   velocidade = 0;
  // }
  // else{
  //   velocidade = 70;
  // }

  // color = leftColorSensor.identify_color2();
  // leftColorSensor.print_color_components_RGB();
  // frontal_distance = frontalUltrassonic.distance_cm();
  // left_distance = leftUltrassonic.distance_cm();
  // Serial.print("A distância frontal é: ");
  // Serial.print(frontal_distance);
  // Serial.print("     E a distância lateral esquerda é: ");
  // Serial.println(left_distance);
  // if (color == 0){
  //   Serial.println("Viiii vermelhoooooo");
  //   velocidade = 0;
  //   LeftMotor.andar_para_frente(&velocidade);
  //   RightMotor.andar_para_frente(&velocidade);
  //   delay(5000);
    
  // }
  
  // while (left_distance < 20){
  //   Serial.println("Preso");
  //   left_distance = leftUltrassonic.distance_cm();
  //   velocidade = 0;
  //   LeftMotor.andar_para_frente(&velocidade);
  //   RightMotor.andar_para_frente(&velocidade);
  // }


  // velocidade = 100;
  // // delay(1000); 
  // LeftMotor.andar_para_frente(&velocidade);
  // RightMotor.andar_para_frente(&velocidade);
}
