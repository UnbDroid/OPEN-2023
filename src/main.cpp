#include<Arduino.h>
#include<Wire.h>
#define Status1 0x02
    #define mpu 0x68
    #define USER_CTRL_AD 0x6A
    #define INT_BYPASS_CONFIG_AD 0x37
    #define mag 0x0C
        #define CNTL1_AD 0x0A   
    // Actually we don't need this step cause the reset value of the register 106 is 0x00
    #define ASAX_AD 0x10  
     #define DATA_READY_MASK 0x01
    #define MAGIC_OVERFLOW_MASK 0x8
void setup(){
    Wire.begin();
    Wire.beginTransmission(mpu);
    Wire.write(USER_CTRL_AD);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.beginTransmission(mpu);
    Wire.write(INT_BYPASS_CONFIG_AD);
    Wire.write(0x02);   //0000 0010 in binary, turn on the bypass multiplexer
    Wire.endTransmission();
    Wire.beginTransmission(mag);
    Wire.write(CNTL1_AD);
    Wire.write(0x1F);
    delay(100);
    Wire.beginTransmission(mag);
    Wire.write(CNTL1_AD);
    Wire.write(0x00);
    //wait for the mode changes
    delay(100);

    Wire.beginTransmission(mag);
    Wire.write(CNTL1_AD);
    Wire.write(0x16);   //0001 0110 in binary

    //wait for the mode changes
    delay(100);
}

void loop(){
  Wire.beginTransmission(mag);
        Wire.write(0x03);
        Wire.requestFrom(mag,7,true);
        float x = Wire.read()<<8|Wire.read();
        Serial.println(x);
        
    
}



    