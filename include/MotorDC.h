/*


NOS ARQUIVOS .H TEREMOS TUDO O QUE A NOSSA CLASSE TERÁ, COMO FUNÇÕES EX: ANDAR PARA FRENTE E ATRIBUTOS POR EXEMPLO
 PINO VELOCIDADE, ETC

TEMOS DIFERENTES TIPOS DE VISUALIZAÇÕES DAS COISAS, COMO PUBLIC, PRIVATE, PROTECTED

*/

#ifndef MOTORDC_H
#define MOTORDC_H
    class MotorDC{
        public: 
            MotorDC(int RPWM,int LPWM);
            MotorDC(int RPWM,int LPWM, int pinEncA,int pinEncB);
            // ~MotorDC();
            void moveForward(int velocity);
            void moveBackward(int velocity);
            void readEncoder();
            void stop();
            int getEncoder();

        private:
            int velocity;
            int pinoA;
            int pinoB;
            int pinoPwm; //de 0 ate 250
            int encA;
            int encB;
            int posEncoder = 0; // no poo, como que ficam esas variáveis
            int pinEncA;
            int pinEncB;
    };
#endif