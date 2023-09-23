#include <Rasp.h>

// Types of cubes
// 'a' to 'i' -> cubes with the letter
// '1' to '9' -> cubes with the 'code'
// 'w', 'x', 'y', 'z' -> red, green, blue, yellow

// '0', returned no cube


char return_type_of_cube(){ 
    char data;
    int i;
    for(i=0; i<100; i++){
    Serial.print("t");      // A letra 'T' significa que o RASP precisa retornar o TIPO cubo na frente dele
  }
    data = Serial.read();
    while (!(data >= 'a' && data <= 'i') && !(data >= '0' && data <= '9') && !(data >= 'w' && data <= 'z')){
    data = Serial.read();
  }
  return data;
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