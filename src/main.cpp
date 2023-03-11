#include "MPU9250.h"
#include<Arduino.h>
#include<math.h>
MPU9250 mpu; // You can also use MPU9255 as is

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address
    mpu.setMagneticDeclination(-21.091666); //minuto/60
    mpu.setMagBias(1,0,0);
}

float Norte = 5.5;//6.5;
float leste = 25;//30;
float oeste = 14;//19;
float sul = 32;//37
void loop() {
    if (mpu.update()) {
      
       Serial.println(mpu.getYaw());
       //Serial.println(((pow(pow(anguloReal,2)+ pow(angulo2, 2), 0.5))*180)/PI);
    }
}
