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


void ColorSensor::normalize_reading(){ // Função que calibra o sensor de cor, fazendo as leituras variarem entre 0 e 1000
  this->red = (this->red - lim_white_r) * (1000/(lim_nothing_r - lim_white_r));
  this->green = (this->green - lim_white_g) * (1000/(lim_nothing_g - lim_white_g));
  this->blue = (this->blue - lim_white_b) * (1000/(lim_nothing_b - lim_white_b));
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

int ColorSensor::identify_color2(){   // Lê os valores dos componentes RGB, identifica a cor e printa o nome da cor
// Para identificar a cor, ele checa se as componentes rgb estão dentro dos limites correspondentes por cada cor, por exemplo:
// Para a cor ser considerada vermelha,a componente R do RGB deve estar entre 20 e 40, a G entre 60 e 80, e a B entre 60 e 80
  
  read_values();
  Serial.println("Entrei");
  normalize_reading();
  
  //Verifica se a cor vermelha foi detectada
  if ((this -> lim_inf_red_r < this->red && this->red < this->lim_sup_red_r ) && this->red < this->blue && this->red < this->green){
    Serial.println("Vermelho");
    return 0;}

  //Verifica se a cor azul foi detectada
  else if ((this -> lim_inf_blue_b < this->blue && this->blue < this -> lim_sup_blue_b) && this->blue < this->red && this->blue < this->green){
    Serial.println("Azul");
    return 1;}

  //Verifica se a cor verde foi detectada
  else if ((this -> lim_inf_green_g < this->green && this->green < this -> lim_sup_green_g) && this->green < this->red && this->green < this->blue){
    Serial.println("Verde");
    return 2;}

    //Verifica se a cor amarela foi detectada
  else if ((this -> lim_inf_yellow_b < this->blue && this->blue < this -> lim_sup_yellow_b) && this->blue > this->red && this->blue > this->green){
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

  int count = num * 84; // Cada sensor de cor ocupa 84 espaços na memória

  // Lendo os valores de nothing

  EEPROM.get(count, this ->lim_nothing_r);
  EEPROM.get(count+2, this ->lim_nothing_g);
  EEPROM.get(count+4, this ->lim_nothing_b);
  count +=6;

  // Lendo os valores do limite branco da calibragem  
  EEPROM.get(count, this ->lim_white_r);
  EEPROM.get(count+2, this ->lim_white_g);
  EEPROM.get(count+4, this ->lim_white_b);
  count +=6;
  
  
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

void ColorSensor::calibra_cor(char cor[20], int count){ // Calibra os limites das cores, já normalizando os valores
  int red_aux, green_aux, blue_aux;

  Serial.print("Calibrando cor versão perto: ");  // Colocar o robô o mais perto possível da cor
  Serial.println(cor);
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();

  // Normalizando os valores na faixa entre 0 a 1000:
  normalize_reading();

  print_color_components_RGB(); // Printando os valores já normalizados
  red_aux = this->red;
  green_aux = this->green;
  blue_aux = this -> blue;

//-------------Versão Longe ----------------------------
  Serial.print("Calibrando cor versão longe: ");
  Serial.println(cor);
  while(!Serial.available()){}
  while (Serial.available()){Serial.read();}
  read_values();

  // Normalizando os valores na faixa entre 0 a 1000:
  normalize_reading();

  print_color_components_RGB(); // Printando os valores já normalizados
 
  

  // ----------------------------------------------------------------------------------------------------------------------------
  if (this->red < red_aux){       /// Colocandos os ranges de vermelho na memória, colocando sempre o limite inferior antes
  EEPROM.put(count+2, red_aux);
  EEPROM.put(count, this->red);
  }
  else{
    EEPROM.put(count, red_aux);
    EEPROM.put(count + 2, this->red);
  }
 // -----------------------------------------------------------------------------------------------------------------------------
  if (this->green < green_aux){       /// Colocandos os ranges de verde na memória, colocando sempre o limite inferior antes
    EEPROM.put(count+6, green_aux);
    EEPROM.put(count+4, this->green);
  }
  else{
    EEPROM.put(count+4, green_aux);
    EEPROM.put(count + 6, this->green);
  }
  //--------------------------------------------------------------------------------------------------------------------------------
  if (this->blue < blue_aux){       /// Colocandos os ranges de azul na memória, colocando sempre o limite inferior antes
    EEPROM.put(count+10, blue_aux);
    EEPROM.put(count+8, this->blue);
  }
  else{
    EEPROM.put(count+8, blue_aux);
    EEPROM.put(count + 10, this->blue);
  }
  
  

  EEPROM.put(count + 4, green_aux);
  EEPROM.put(count + 6, this->green);  
  EEPROM.put(count + 8, blue_aux);
  EEPROM.put(count + 10, this->blue);

}


void ColorSensor::calibra_sensor(int num) {
  

  int count;
  char cor[20];
  
  count  = num * 84; // Cada sensor de cor utiliza 78 espaços de memória para armazenar os dados das 6 cores (72 espaços) e do vazio e branco (12 espaços)

  Serial.println("Calibrando com nada perto do sensor: ");  // Tirar qualquer coisa de perto do sensor
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  print_color_components_RGB();
  EEPROM.put(count, this->red);
  EEPROM.put(count+2, this->green);
  EEPROM.put(count+4, this->blue);
  lim_nothing_r = this->red;
  lim_nothing_g = this->green;
  lim_nothing_b = this->blue;
  count +=6;
  

  Serial.println("Calibrando com papel branco: ");  // Colocar a coisa mais branca possível no sensor
  while(!Serial.available()){}                  // Espera até que uma tecla seja clicada (NÃO CLICAR O ENTER POIS SÃO 2 CARACTERES)
  while (Serial.available()){Serial.read();}  // Limpa os bytes de entrada, fazendo com que a outra tecla tenha que ser clicada novamente na próxima leitura
  read_values();
  print_color_components_RGB();
  EEPROM.put(count, this->red);
  EEPROM.put(count+2, this->green);
  EEPROM.put(count+4, this->blue);
  lim_white_r = this->red;
  lim_white_g = this->green;
  lim_white_b = this->blue;

  count +=6;

  strcpy(cor, "Vermelho");
  calibra_cor(cor, count);

  strcpy(cor, "Azul");
  calibra_cor(cor, count+12);

  strcpy(cor, "Verde");
  calibra_cor(cor, count+24);

  strcpy(cor, "Amarelo");
  calibra_cor(cor, count+36);

  strcpy(cor, "Branco");
  calibra_cor(cor, count+48);

  strcpy(cor, "Preto");
  calibra_cor(cor, count+60);

  while(!Serial.available()){}
}
