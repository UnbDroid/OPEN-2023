/*


NOS ARQUIVOS .H TEREMOS TUDO O QUE A NOSSA CLASSE TERÁ, COMO FUNÇÕES EX: ANDAR PARA FRENTE E ATRIBUTOS POR EXEMPLO
 PINO VELOCIDADE, ETC

TEMOS DIFERENTES TIPOS DE VISUALIZAÇÕES DAS COISAS, COMO PUBLIC, PRIVATE, PROTECTED

*/

#ifndef MOTORDC_H
#define MOTORDC_H
    class MotorDC{
        public: 
            MotorDC(int pinoA, int pinoB, int pinoPwm, int pinEnc);
            MotorDC(int pinoA, int pinoB, int pinoPwm);
            // ~MotorDC();
            void moveFoward(int *velocity);
            void moveBackward(int *velocity);
            void stop();

        private:
            int velocity;
            int pinoA;
            int pinoB;
            int pinoPwm; //de 0 ate 250
            int pinEnc;
            
    };
#endif