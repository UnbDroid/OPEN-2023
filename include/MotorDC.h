/*


NOS ARQUIVOS .H TEREMOS TUDO O QUE A NOSSA CLASSE TERÁ, COMO FUNÇÕES EX: ANDAR PARA FRENTE E ATRIBUTOS POR EXEMPLO
 PINO VELOCIDADE, ETC

TEMOS DIFERENTES TIPOS DE VISUALIZAÇÕES DAS COISAS, COMO PUBLIC, PRIVATE, PROTECTED

*/

#ifndef MOTORDC_H
#define MOTORDC_H
    class MotorDC{
        public: 
            MotorDC(int pinoLpwm, int pinoRpwm, int pinoEN, int pinEncA, int pinEncB);
            // MotorDC(int pinoA, int pinoB, int pinoPwm);
            // ~MotorDC();
            void moveForward(int velocity);
            void moveBackward(int velocity);
            void readEncoder();
            void stop();
            int getEncoder();
            int setEncoder(int value);

        private:
            int velocity;
            int pinoRpwm;
            int pinoLpwm;
            int pinoEN;
            int posEncoder = 0; 
            int pinEncA;
            int pinEncB;
            int value;
    };
#endif