#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H
#include<MPU9250.h>

class Giroscopio:public MPU9250{
    public:
    Giroscopio();
    ~Giroscopio();
    float angulo_atual();
    private:

};

#endif