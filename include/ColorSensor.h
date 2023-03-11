#ifndef COLORSENSOR_H
#define COLORSENSOR_H


class ColorSensor{
    public:
        ColorSensor(int s0, int s1, int s2, int s3, int out);

        void read_values();
        void print_color_components_RGB();
        void calibra_sensor(int num);
        int identify_color();
        int identify_color2();
        void read_limit_values(int num);
        void calibra_cor(char cor[20], int count);
        void normalize_reading();


    private:
        int s0;
        int s1;
        int s2;
        int s3;
        int out;
        int red;
        int green;
        int blue;
        int no_filter;
        int last_red;
        int last_green;
        int last_blue;

        int lim_inf_red_r;  
        int lim_sup_red_r;
        int lim_inf_red_g;
        int lim_sup_red_g;
        int lim_inf_red_b;
        int lim_sup_red_b;

        int lim_inf_blue_r;
        int lim_sup_blue_r;
        int lim_inf_blue_g;
        int lim_sup_blue_g;
        int lim_inf_blue_b;
        int lim_sup_blue_b;

        int lim_inf_green_r;
        int lim_sup_green_r;
        int lim_inf_green_g;
        int lim_sup_green_g;
        int lim_inf_green_b;
        int lim_sup_green_b;

        int lim_inf_yellow_r;
        int lim_sup_yellow_r;
        int lim_inf_yellow_g;
        int lim_sup_yellow_g;
        int lim_inf_yellow_b;
        int lim_sup_yellow_b;

        int lim_inf_white_r;
        int lim_sup_white_r;
        int lim_inf_white_g;
        int lim_sup_white_g;
        int lim_inf_white_b;
        int lim_sup_white_b;

        int lim_inf_black_r;
        int lim_sup_black_r;
        int lim_inf_black_g;
        int lim_sup_black_g;
        int lim_inf_black_b;
        int lim_sup_black_b;

        int lim_nothing_r;    // São os valores da leitura dos sensores quando não tem nada na frente do sensor
        int lim_nothing_g;
        int lim_nothing_b;

        int lim_white_r;  // Valores da leitura do Papel branco para calibragem - NÃO CONFUNDIR COM LEITURA DO CUBO/CHÃO BRANCO
        int lim_white_g;
        int lim_white_b;


    

};
#endif