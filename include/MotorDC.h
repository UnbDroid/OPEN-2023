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
            ~MotorDC();
            
            void andar_para_frente(int* velocidade);
            void andar_para_tras(int * velocidade);
            void parar();

        private:
            int velocidade;
            int pinoA;
            int pinoB;
            int pinoPwm; //de 0 ate 250
    };
#endif