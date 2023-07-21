/*


NOS ARQUIVOS .H TEREMOS TUDO O QUE A NOSSA CLASSE TERÁ, COMO FUNÇÕES EX: ANDAR PARA FRENTE E ATRIBUTOS POR EXEMPLO
 PINO VELOCIDADE, ETC

TEMOS DIFERENTES TIPOS DE VISUALIZAÇÕES DAS COISAS, COMO PUBLIC, PRIVATE, PROTECTED

*/

#ifndef MOTORDC_H
#define MOTORDC_H
    class MotorDC{
        public: 
        
            MotorDC(int pinoA, int pinoB, int pinoPwm);
            // ~MotorDC();
            void andar_para_frente(int velocidade);
            void andar_para_tras(int velocidade);
            void parar();
            void readEncoder_right();
            void readEncoder_left();
            int getEncoderRight();
            int getEncoderLeft();

        private:
            int velocidade;
            int pinoA;
            int pinoB;
            int pinoPwm; //de 0 ate 250
            int enca_right;
            int encb_right;
            int enca_left;
            int encb_left;
            int pos_encoder_right = 0; // no poo, como que ficam esas variáveis
            int pos_encoder_left = 0;

            
    };
#endif