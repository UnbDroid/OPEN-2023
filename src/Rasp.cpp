#include <Rasp.h>

// Types of cubes
// 'a' to 'i' -> cubes with the letter
// '1' to '9' -> cubes with the 'code'
// 'w', 'x', 'y', 'z' -> red, green, blue, yellow

// '0', returned no cube


char return_type_of_cube(){ 
    char data;
    int i, counter = 1;
    unsigned long startTime, loopDuration;
    while (counter <= 0){
    for(i=0; i<1000; i++){
    Serial.print("t");      // A letra 'T' significa que o RASP precisa retornar o TIPO cubo na frente dele
  }
    data = Serial.read();
    startTime = millis();
    loopDuration = 10000;
    while ((!(data >= 'a' && data <= 'i') && !(data >= '0' && data <= '9') && !(data >= 'w' && data <= 'z')) && millis() - startTime < loopDuration ){
    data = Serial.read();
  }
    if ((data >= 'a' && data <= 'i') || (data >= '0' && data <= '9') || (data >= 'w' && data <= 'z'))
        return data;
    counter ++;
    }
    return '0';
}



// Retorna 's' se viu uma prateleira, e 'n' se não viu uma prateleira

char return_shelves(){ 
    char data;
    int i;
    for(i=0; i<100; i++){
    Serial.print("p");      // A letra 'p' significa que o RASP precisa retornar se há ou não uma prateleira na frente dele
  }
    data = Serial.read();
    while (data != 's' && data != 'n'){
    data = Serial.read();
  }
  return data;
}



int return_count_of_cubes(){ 
    char data;
    int i;
    unsigned long startTime, loopDuration;
    while (1){
    for(i=0; i<100; i++){
    Serial.print("k");      // A letra 'K' significa que o RASP precisa retornar a contagem dos cubos na frente dele
  }
    data = Serial.read();
    startTime = millis();
    loopDuration = 10000;
    while (!(data >= '0' && data <= '9') && millis() - startTime < loopDuration ){
    data = Serial.read();
  }
    if ((data >= '0' && data <= '9')){
        i = data - '0';
        return i;
        }
    }
}


