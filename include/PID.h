#ifndef PID_H
#define PID_H
    class SimplePID{

    private:
    float kp,kd,ki,umax, umin; // parameters
    float erroPrevious, eintegral; // Storag
    int ENCA, ENCB; // pins
    
    public:
    // contrutor que seta os parametros sempre que o obj é criado:
    SimplePID(int kp, int kd, int ki, int umax, int erroPrevious, int eintegral, int ENCA, int ENCB);
    int controlValue(int positionRight, int positionLeft, int target, float deltaT, int &pwr, int KP, int KD, int KI); 
    void readEncoder(int pinoA, int posicao);
    void setMotorsPID(int sumPID, int umax, int umin)
    
    
    };

#endif