#include <Wire.h>
#include<Arduino.h>

#define MPU9250_ADDRESS 0x69
#define MAG_ADDRESS 0x0C

// Registradores do magnetômetro
#define MAG_XOUT_L 0x03
#define MAG_XOUT_H 0x04
#define MAG_YOUT_L 0x05
#define MAG_YOUT_H 0x06
#define MAG_ZOUT_L 0x07
#define MAG_ZOUT_H 0x08

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Configurar o MPU-9250 para ligar o magnetômetro
  Wire.beginTransmission(MPU9250_ADDRESS);
  Wire.write(0x6A); // registrador PWR_MGMT_2
  Wire.write(0x00); // ativar todos os sensores
  Wire.endTransmission();
  
  // Configurar o magnetômetro para taxa de amostragem de 100 Hz
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(0x0A); // registrador CNTL1
  Wire.write(0x16); // taxa de amostragem = 100 Hz
  Wire.endTransmission();
}

void loop() {
  // Ler os dados brutos da bússola
  Wire.beginTransmission(MAG_ADDRESS);
  Wire.write(MAG_XOUT_L);  //de onde eu quero começar a receber os dados 
  Wire.endTransmission();
  Wire.requestFrom(MAG_ADDRESS, 6, true );
  byte xlo = Wire.read();
  byte xhi = Wire.read();
  byte ylo = Wire.read();
  byte yhi = Wire.read();
  byte zlo = Wire.read();
  byte zhi = Wire.read();

  // Converter os dados brutos em valores de campo magnético em Gauss
  int16_t x = (int16_t)(xhi << 8 | xlo);
  int16_t y = (int16_t)(yhi << 8 | ylo);
  int16_t z = (int16_t)(zhi << 8 | zlo);
  float mag_x = (float)x / 32768.0 * 4800.0;
  float mag_y = (float)y / 32768.0 * 4800.0;
  float mag_z = (float)z / 32768.0 * 4800.0;
  Serial.print(mag_x);
  Serial.print(" ");
  Serial.print(mag_y);
  Serial.print(" ");
  Serial.println(mag_z);
  // Calcular a direção da bússola em graus
  float heading = atan2(mag_y, mag_x) * 180.0 / PI;
  if (heading < 0) {
    heading += 360.0;
  }

  Serial.println(heading);
  delay(100);
}