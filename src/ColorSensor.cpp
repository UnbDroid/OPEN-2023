#include<ColorSensor.h>
#include<Arduino.h>
#include<Wire.h>
#include <EEPROM.h>




ColorSensor::ColorSensor(int s0, int s1, int s2, int s3, int out){
    this->s0 = s0;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    this->out = out;
    pinMode(this->s0, OUTPUT);
    pinMode(this->s1, OUTPUT);
    pinMode(this->s2, OUTPUT);
    pinMode(this->s3, OUTPUT);
    pinMode(this->out, INPUT);

    digitalWrite(this->s0, HIGH);
    digitalWrite(this->s1, LOW);


}

void ColorSensor::read_values(){  //Rotina que lê as componentes RGB do sensor. Não é para ser chamada na main
  digitalWrite(this->s2, LOW);
  digitalWrite(this->s3, LOW);
  //count OUT, pRed, RED
  this->red = pulseIn(this->out, HIGH);
  digitalWrite(this->s3, HIGH);
  //count out, pBLUE, BLUE
  this->blue = pulseIn(this->out, HIGH);
  digitalWrite(this->s2, HIGH);
  //count out, pGreen, GREEN
  this->green = pulseIn(this->out, HIGH);
  digitalWrite(this->s3, LOW);
  // count out -> no filter
  this->no_filter = pulseIn(this->out, HIGH);
}





int ColorSensor::identify_color(){   // Lê os valores dos componentes RGB, identifica a cor e printa o nome da cor
// Para identificar a cor, ele checa se as componentes rgb estão dentro dos limites correspondentes por cada cor, por exemplo:
// Para a cor ser considerada vermelha,a componente R do RGB deve estar entre 20 e 40, a G entre 60 e 80, e a B entre 60 e 80
  

  read_values();
  
  //Verifica se a cor vermelha foi detectada
  if ((this -> lim_inf_red_r < this->red && this->red < this->lim_sup_red_r ) && (this -> lim_inf_red_g < this->green && this->green < this -> lim_sup_red_g) && (this -> lim_inf_red_b < this->blue && this->blue < this -> lim_sup_red_b) && this->red < this->blue && this->red < this->green){
    Serial.println("Vermelho");
    return 0;}

  //Verifica se a cor azul foi detectada
  else if ((this -> lim_inf_blue_r < this->red && this->red < this->lim_sup_blue_r ) && (this -> lim_inf_blue_g < this->green && this->green < this -> lim_sup_blue_g) && (this -> lim_inf_blue_b < this->blue && this->blue < this -> lim_sup_blue_b) && this->blue < this->red && this->blue < this->green){
    Serial.println("Azul");
    return 1;}

  //Verifica se a cor verde foi detectada
  else if ((this -> lim_inf_green_r < this->red && this->red < this->lim_sup_green_r ) && (this -> lim_inf_green_g < this->green && this->green < this -> lim_sup_green_g) && (this -> lim_inf_green_b < this->blue && this->blue < this -> lim_sup_green_b)&& this->green < this->red && this->green < this->blue){
    Serial.println("Verde");
    return 2;}

    //Verifica se a cor amarela foi detectada
  else if ((this -> lim_inf_yellow_r < this->red && this->red < this->lim_sup_yellow_r ) && (this -> lim_inf_yellow_g < this->green && this->green < this -> lim_sup_yellow_g) && (this -> lim_inf_yellow_b < this->blue && this->blue < this -> lim_sup_yellow_b) && this->blue > this->red && this->blue > this->green){
    Serial.println("Amarelo");
    return 3;}

    //Verifica se a cor branca foi detectada
  else if ((this -> lim_inf_white_r < this->red && this->red < this->lim_sup_white_r ) && (this -> lim_inf_white_g < this->green && this->green < this -> lim_sup_white_g) && (this -> lim_inf_white_b < this->blue && this->blue < this -> lim_sup_white_b)) {
    Serial.println("Branco");
    return 4;}

    //Verifica se a cor preta foi detectada
  else if ((this -> lim_inf_black_r < this->red && this->red < this->lim_sup_black_r ) && (this -> lim_inf_black_g < this->green && this->green < this -> lim_sup_black_g) && (this -> lim_inf_black_b < this->blue && this->blue < this -> lim_sup_black_b)) {
    Serial.println("Preto");
    return 5;}

  else{
    Serial.println("Nenhuma Cor Identificada");
    return 6;
  }

}



void ColorSensor::print_color_components_RGB(){

  //Mostra valores no serial monitor
  Serial.print("Vermelho:");
  Serial.print(this->red, DEC);
  Serial.print("    Verde :");
  Serial.print(this->green, DEC);
  Serial.print("    Azul :");
  Serial.print(this->blue, DEC);
  Serial.print("    No Filter : ");
  Serial.print(this->no_filter, DEC);
  Serial.println();

}

void ColorSensor::read_limit_values(int num){ // Função que lê os valores dos limites dos ranges de cores que estão armazenados na memória do arduíno
    // num == 0 -> Sensor de Cor Frontal
  // num == 1 -> Sensor de Cor Inferior Esquerdo
  // num == 2 -> Sensor de Cor Superior Esquerdo

  int count = num * 72; // Cada sensor de cor ocupa 72 espaços na memória
  
  // Lendo os valores da cor vermelha
  EEPROM.get(count, this ->lim_inf_red_r);
  EEPROM.get(count + 2, this ->lim_sup_red_r);

  EEPROM.get(count + 4, this ->lim_inf_red_g);
  EEPROM.get(count + 6, this ->lim_sup_red_g);

  EEPROM.get(count+8, this ->lim_inf_red_b);
  EEPROM.get(count + 10, this ->lim_sup_red_b);




  // Lendo os valores da cor azul
  count +=12;
  EEPROM.get(count, this ->lim_inf_blue_r);
  EEPROM.get(count + 2, this ->lim_sup_blue_r);

  EEPROM.get(count + 4, this ->lim_inf_blue_g);
  EEPROM.get(count + 6, this ->lim_sup_blue_g);

  EEPROM.get(count+8, this ->lim_inf_blue_b);
  EEPROM.get(count + 10, this ->lim_sup_blue_b);

  // Lendo os valores da cor verde
  count +=12;
  EEPROM.get(count, this ->lim_inf_green_r);
  EEPROM.get(count + 2, this ->lim_sup_green_r);

  EEPROM.get(count + 4, this ->lim_inf_green_g);
  EEPROM.get(count + 6, this ->lim_sup_green_g);

  EEPROM.get(count+8, this ->lim_inf_green_b);
  EEPROM.get(count + 10, this ->lim_sup_green_b);

  // Lendo os valores da cor amarela
  count +=12;
  EEPROM.get(count, this ->lim_inf_yellow_r);
  EEPROM.get(count + 2, this ->lim_sup_yellow_r);

  EEPROM.get(count + 4, this ->lim_inf_yellow_g);
  EEPROM.get(count + 6, this ->lim_sup_yellow_g);

  EEPROM.get(count+8, this ->lim_inf_yellow_b);
  EEPROM.get(count + 10, this ->lim_sup_yellow_b);


  // Lendo os valores da cor branca
  count +=12;
  EEPROM.get(count, this ->lim_inf_white_r);
  EEPROM.get(count + 2, this ->lim_sup_white_r);

  EEPROM.get(count + 4, this ->lim_inf_white_g);
  EEPROM.get(count + 6, this ->lim_sup_white_g);

  EEPROM.get(count+8, this ->lim_inf_white_b);
  EEPROM.get(count + 10, this ->lim_sup_white_b);

  // Lendo os valores da cor preta
  count +=12;
  EEPROM.get(count, this ->lim_inf_black_r);
  EEPROM.get(count + 2, this ->lim_sup_black_r);

  EEPROM.get(count + 4, this ->lim_inf_black_g);
  EEPROM.get(count + 6, this ->lim_sup_black_g);

  EEPROM.get(count+8, this ->lim_inf_black_b);
  EEPROM.get(count + 10, this ->lim_sup_black_b);

}

void ColorSensor::calibra_cor(char cor[20], int count){
  int red_aux, green_aux, blue_aux;

  count  = num * 72;
  // Calibrando cor vermelha
  Serial.println("Calibrando cor Vermelha - Versão Perto");  // Colocar o robô o mais perto possível do azul
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green); // Cada inteiro é salvo em 2 bytes, por isso o primeiro argumento da função é sempre par
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor Vermelha - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando cor azul
  Serial.println("Calibrando cor azul - Versão Perto");  // Colocar o robô o mais perto possível do azul
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor azul - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando cor verde
  Serial.println("Calibrando cor verde - Versão Perto");  // Colocar o robô o mais perto possível do verde
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor verde - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando amarelo
  Serial.println("Calibrando cor amarelo - Versão Perto");  // Colocar o robô o mais perto possível do amarelo
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor amarelo - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();


  count += 12;
  // Calibrando cor branco
  Serial.println("Calibrando cor branco - Versão Perto");  // Colocar o robô o mais perto possível do branco
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor branco - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

void ColorSensor::calibra_sensor(int num) {
  

  int count;
  
  count  = 0;
  // Calibrando cor vermelha
  Serial.println("Calibrando cor Vermelha - Versão Perto");  // Colocar o robô o mais perto possível do azul
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green); // Cada inteiro é salvo em 2 bytes, por isso o primeiro argumento da função é sempre par
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor Vermelha - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando cor azul
  Serial.println("Calibrando cor azul - Versão Perto");  // Colocar o robô o mais perto possível do azul
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor azul - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando cor verde
  Serial.println("Calibrando cor verde - Versão Perto");  // Colocar o robô o mais perto possível do verde
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor verde - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando amarelo
  Serial.println("Calibrando cor amarelo - Versão Perto");  // Colocar o robô o mais perto possível do amarelo
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor amarelo - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();


  count += 12;
  // Calibrando cor branco
  Serial.println("Calibrando cor branco - Versão Perto");  // Colocar o robô o mais perto possível do branco
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor branco - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);
  print_color_components_RGB();

  count += 12;
  // Calibrando cor preto
  Serial.println("Calibrando cor preto - Versão Perto");  // Colocar o robô o mais perto possível do preto
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  EEPROM.put(count, this->red);
  EEPROM.put(count + 4, this->green);
  EEPROM.put(count + 8, this->blue);
  print_color_components_RGB();


  Serial.println("Calibrando cor preto - Versão Longe");
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();
  EEPROM.put(count + 2, this->red);
  EEPROM.put(count + 6, this->green);
  EEPROM.put(count + 10, this->blue);   
  print_color_components_RGB();
}
