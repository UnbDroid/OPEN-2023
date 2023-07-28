#include "MPU9250.h"
#include<Arduino.h>
// USAR ESSE CÓDIGO
MPU9250 mpu;

//******************************************************
// COMO FUNCIONA?
// 1° Você irá procurar a declinação magnetica do local para assim poder calibralo é o minuto/60
// exemplo de declinação magnética  mpu.setMagneticDeclination(-21.091666); //minuto/60;

// 2 °vamos executar o arquivo serial_port.py
// pois ele irá ler os dados que estão sendo printados no serial e irá guardar no arquivo leituras.csv
// e plotará na tela como foi a leitura bruta, e as leituras caso aplique os valores de calibragem que ele mostrar
// e depois disso é só setar isso no mpu com o setMagBias e setMagScale

// 3° Você irá rodar o código printarMagnetometroPuro no void loop, no qual o mesmo irá so 
// printar os dados brutos, pois é com esses dados que iremos calibrar o sensor. Você vai precisar
//ficar girando o magnetometro no eixo x-y até ele terminar as leituras
// pois assim ele irá variar os valores, e com isso teremos
// os valores máximos e mínimos para a nossa calibração

//4° pegar os valores printados da calibração e setar com o mpu


//******************************************************
void printarMagnetometroPuro() {
        if(mpu.update()){
        static uint32_t tempo = millis(); //colocarei um delay de 25 milisegundos
        if(millis()>tempo+25){
            Serial.print(mpu.getMagX());
            Serial.print(" ");
            Serial.println(mpu.getMagY());
            tempo = millis();
        }
    }
}

void printarValoresEmGraus(){
    if(mpu.update()){
        static uint32_t tempo = millis(); //colocarei um delay de 25 milisegundos
        if(millis()>tempo+25){
            float angulo = atan2(mpu.getMagX(), mpu.getMagY());
            Serial.println(angulo*180/PI);
            tempo = millis();
        }
    }
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(2000);
    if (!mpu.setup(0x68)) {  // Endereço do MPU 
        while (1) {
            Serial.println("Conexão com o MPU FALHOU");
        }
    }
    mpu.setMagneticDeclination(-21.091666);
    Serial.print("Mag X, ");   
    Serial.println("Mag y " );  
}
void coletarValoresParaCalibracao(){
    if(mpu.update()){
        static uint32_t tempo = millis(); //colocarei um delay de 25 milisegundos
        if(millis()>tempo+25){
            printarMagnetometroPuro();
            tempo = millis();
        }
    }
}

void loop() {
    coletarValoresParaCalibracao();
}


