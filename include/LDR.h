
#ifndef LDR_H
#define LDR_H

    class LDR{
        public:
            LDR::LDR(int pinLDR);

            int read();

        private:
            int pinLDR;
    };




#endif