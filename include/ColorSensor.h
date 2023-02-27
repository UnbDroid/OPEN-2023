#ifndef COLORSENSOR_H
#define COLORSENSOR_H


class ColorSensor{
    public:
        ColorSensor(int s0, int s1, int s2, int s3, int out);

        void read_values();
        void print_color_components_RGB();
        int identify_color(int num);


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

};
#endif