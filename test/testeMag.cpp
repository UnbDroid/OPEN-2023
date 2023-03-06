#include<Arduino.h>
#include<Wire.h>

#define mpu9250_addr 0x68 //endereço MPU
#define magn_addr 0x0C //Endereço do magnetometro 
#define PWR_MGMT_1 0x6b //registrador de configuração de energia
#define PWR_MGMT_2 0x6c //registrador de configuração de energia
#define INT_PIN_CFG 0x37
#define CONFIG 0x1a
#define SMPLRT_DIV 0x19
#define CNTL1 0x0a
#define MAG_XOUT_L 0x03
void setup(){
    Serial.begin(9600);
  Wire.begin();
  //  Reseta os valores dos registradores 
  Wire.beginTransmission(mpu9250_addr);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x80);
  Wire.endTransmission();
  //
  //desabilita o sleep seta o clock automaticamente
  Wire.beginTransmission(mpu9250_addr);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x01);
  Wire.endTransmission();
  //
  //
  Wire.endTransmission(mpu9250_addr);
  Wire.write(INT_PIN_CFG);
  Wire.write(0x02);
  Wire.endTransmission();
  //
  // Setando o modo de energia do magnetometro
  Wire.beginTransmission(magn_addr);
  Wire.write(PWR_MGMT_2);
  Wire.write(0x00);
  Wire.endTransmission();
  //
  // Seta a configuração dos registradores
  Wire.beginTransmission(mpu9250_addr);
  Wire.write(CONFIG);
  Wire.write(0x03);
  Wire.endTransmission();
  //

  Wire.beginTransmission(mpu9250_addr);
  Wire.write(SMPLRT_DIV);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(magn_addr);
  Wire.write(CNTL1);
  Wire.write(0x16);
  Wire.endTransmission();
  //
}
#define a1 0x02;
#define a2 0x01;
float magx, magy,magz;
void loop(){
  Wire.beginTransmission(magn_addr);
  Wire.write(MAG_XOUT_L);  //de onde eu quero começar a receber os dados 
  Wire.endTransmission();
  Wire.requestFrom(mpu9250_addr, 6, true);
  magx = Wire.read()<<8 | Wire.read();
  magy = Wire.read()<<8 | Wire.read();
  magz = Wire.read()<<8 | Wire.read();

  Serial.println(magx);
  delay(1000);
}