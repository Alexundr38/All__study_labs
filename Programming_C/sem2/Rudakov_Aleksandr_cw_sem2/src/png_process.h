#ifndef PNG_PROCESS
#define PNG_PROCESS

#include <png.h>

typedef struct png{
    int width, height;
    png_structp png_ptr;
    png_infop info_ptr;
    png_byte color_type;
    png_byte bit_depth;
    int number_of_passes;
    png_bytep *row_pointers;
} png;

void inf(png* image);

void read_png(char *file_name, png *image);

void write_png(char *file_name, png *image);

void rgb_filter(png *image, char *component_name, int component_value);

void rgb_split(png *image, int number_x, int number_y, int thikness, int red, int green, int blue);

void circle(png *image, int x0, int y0, int radius, int thikness, int red, \
    int green, int blue, int fill, int fill_red, int fill_green, int fill_blue);

void rgb_contrast(png *image, double alpha, int beta);

void rgb_blur(png *image, int size);

#endif