#include<Mag.h>
void Mag::printPureMagToCalibrate(){
       if(this->update()){
        static uint32_t tempo = millis(); //colocarei um delay de 25 milisegundos
        if(millis()>tempo+25){
            Serial.print(this->getMagX());
            Serial.print(" ");
            Serial.println(this->getMagY());
            tempo = millis();
        }
    }
};
Mag::Mag(){

};
char Mag::getDirection(){
    float degree = this->getDegree();
    if(degree>=45 && degree<=135){
        return 'N';
    }
    else if(degree>=135 && degree<=225){
        return 'O';
    }
    else if(degree>=225 && degree<=315){
        return 'S';
    }
    else{
        return 'L';
    }
};
void Mag::setCorrection(int ShelfsDegree){
    if(ShelfsDegree<=90){
        this->correction= 90-ShelfsDegree;
    }
    else{
        this->correction= -ShelfsDegree+90;
    }
};
int Mag::getCorrection(){
    return this->correction;
}
float Mag::getDegree(){
    if(this->update()){
        static uint32_t tempo = millis(); //colocarei um delay de 25 milisegundos
        if(millis()>tempo+25){
            float angulo = atan2(this->getMagX(), this->getMagY());
            angulo = angulo*180/PI;
            angulo+= this->getCorrection();
            tempo = millis();
            return angulo<0?angulo+360:angulo;
        }
    }
};

