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
}


void loop() {
    if (mpu.update()) {
        float x = pow(mpu.getMagX(),2);
        float y = pow(mpu.getMagY(),2);
        float z = pow(mpu.getMagZ(),2);
        float result = x+y+z;
        float B = sqrt(result);
        float anguloInclinacao = asin(-mpu.getMagY()/B);
        float roll = atan2(mpu.getMagX(),mpu.getMagY());
        float angulo = (roll *180)/PI;
        //Serial.println((angulo*2)-10);
        
        float anguloReal = (mpu.getYaw());
       Serial.println(anguloReal);
    }
}
