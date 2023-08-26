#ifndef __MAG_H
#define __MAG_H
#include<MPU9250.h>

class Mag:public MPU9250{
    public:
        Mag();
        int  getCorrection();
        void setCorrection(int ShelfsDegree);
        char getDirection();
        void printPureMagToCalibrate();
        void printarValoresEmGraus();
        float getDegree();
    private:
        float degree;
        int correction;
};
#endif
