#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>
#include "png_process.h"
#include "additional_functions.h"


void inf(png* image){
    printf("width - %d.\n", image->width);
    printf("height - %d.\n", image->height);
    printf("color type - %u.\n", image->color_type);
    printf("bit_depth - %u.\n", image->bit_depth);
}

void set_pixel(png *image, int x, int y, int red, int green, int blue){
    image->row_pointers[y][x * 3] = red;
    image->row_pointers[y][x * 3 + 1] = green;
    image->row_pointers[y][x * 3 + 2] = blue;
}

void read_png(char *file_name, png *image){
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        puts("Error: the file could be opened");
        exit(43);
    }

    char header[8];
    fread(header, 1, 8, fp);
    if (!png_check_sig(header, 8)){
        puts("Error: the file isn't PNG");
        exit(43);
    }

    image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        puts("Error: failed to create a structure of image");
        exit(42);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        puts("Error: failed to create a structure of image");
        exit(42);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error: image reading error");
        exit(42);
    }
    png_init_io(image->png_ptr, fp);
    png_set_sig_bytes(image->png_ptr, 8);
    png_read_info(image->png_ptr, image->info_ptr);
    image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    image->color_type = png_get_color_type(image->png_ptr,image->info_ptr);
    image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);
    image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    png_read_update_info(image->png_ptr, image->info_ptr);

    image->row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
    for (size_t i = 0; i < image->height; i++){
        image->row_pointers[i] = (png_byte*)malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
    }
    png_read_image(image->png_ptr, image->row_pointers);

    fclose(fp);
}

void write_png(char *file_name, png *image){
    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        puts("Error: the file could be opened");
        exit(43);
    }

    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!image->png_ptr){
        puts("Error: failed to create a structure of image");
        exit(42);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        puts("Error: failed to create a structure of image");
        exit(42);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error: image recording error");
        exit(42);
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error: image recording error");
        exit(42);
    }
    
    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, \
        image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    png_write_info(image->png_ptr, image->info_ptr);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        puts("Error: image recording error");
        exit(42);
    }

    png_write_image(image->png_ptr, image->row_pointers);
    png_write_end(image->png_ptr, NULL);
    fclose(fp);
}

void rgb_filter(png *image, char *component_name, int component_value){
    if (strstr(component_name, "red")){
        for (int y = 0; y < image->height; y++){
            for (int x = 0; x < image->width; x++){
                image->row_pointers[y][x * 3] = component_value;
            }   
        }
    } else if (strstr(component_name, "green")){
        for (int y = 0; y < image->height; y++){
            for (int x = 0; x < image->width; x++){
                image->row_pointers[y][x * 3 + 1] = component_value;
            }   
        }
    } else if (strstr(component_name, "blue")){
        for (int y = 0; y < image->height; y++){
            for (int x = 0; x < image->width; x++){
                image->row_pointers[y][x * 3 + 2] = component_value;
            }   
        }
    } else {                                                                                                //incorrect color
        puts("error: incorrect color");
        exit(0);
    }
}

void rgb_split(png *image, int number_x, int number_y, int thikness, int red, int green, int blue){
    int line_x, line_y;
    line_x = (image->width - ((number_x - 1) * thikness)) / number_x;
    line_y = (image->height - ((number_y - 1) * thikness)) / number_y;

    if (line_x <= 0 || line_y <= 0){
        for (int y = 0; y < image->height; y++){
            for (int x = 0; x < image->width; x++){
                set_pixel(image, x, y, red, green, blue);
            }   
        }
    } else {
        for (int i = line_x; i < image->width - thikness; i += line_x + thikness){
            for (int x = i; x < i + thikness; x++){
                for (int y = 0; y < image->height; y++){
                    set_pixel(image, x, y, red, green, blue);
                }
            }
        }

        for (int i = line_y; i < image->height - thikness; i += line_y + thikness){
            for (int y = i; y < i + thikness; y++){
                for (int x = 0; x < image->width; x++){
                    set_pixel(image, x, y, red, green, blue);
                }
            }
        }
    }
}

void circle(png *image, int x0, int y0, int radius, int thikness, int red, \
    int green, int blue, int fill, int fill_red, int fill_green, int fill_blue){

        int delta = thikness / 2;
        if (delta == 0){
            delta++;
        }
        for (int x = max(0, x0 - (radius + delta)); x <= min(image->width - 1, x0 + (radius + delta)); x++){
            for (int y = max(0, y0 - (radius + delta)); y <= min(image->height - 1, y0 + (radius + delta)); y++){
                int left = (x-x0) * (x-x0) + (y-y0) * (y-y0);
                int right_max = (radius + delta) * (radius + delta);
                int right_min = 0;
                if (delta < radius){
                    right_min = (radius - delta) * (radius - delta);
                }
                if (left <= right_max && left >= right_min){
                    set_pixel(image, x, y, red, green, blue);
                }
                if (fill != 0){
                    if (left < right_min){
                        set_pixel(image, x, y, fill_red, fill_green, fill_blue);
                    }
                }
            }
        }
    }

void rgb_contrast(png *image, double alpha, int beta){
    for (int y = 0; y < image->height; y++){
        for (int x = 0; x < image->width; x++){
            int red = image->row_pointers[y][x * 3] * alpha + beta;
            int green = image->row_pointers[y][x * 3 + 1] * alpha + beta;
            int blue = image->row_pointers[y][x * 3 + 2] * alpha + beta;
            if (red>255){
                red = 255;
            }
            if (green > 255){
                green = 255;
            }
            if (blue > 255){
                blue = 255;
            }
            set_pixel(image, x, y, red, green, blue);
        }
    }
}

void rgb_blur(png *image, int size){
    if (size % 2 == 0) size++;
    png_bytep* row = (png_bytep*)malloc(image->height * sizeof(png_bytep));
    for (int y = 0; y < image->height; y++){
        row[y] = (png_bytep)malloc(3 * image->width * sizeof(png_byte));
        for (int x = 0; x < image->width; x++){
            row[y][x * 3] = image->row_pointers[y][x * 3];
            row[y][x * 3 + 1] = image->row_pointers[y][x * 3 + 1];
            row[y][x * 3 + 2] = image->row_pointers[y][x * 3 + 2];
            /*if (x<200 && x>196 && y<200 && y>196){
                printf("%d %d {%d %d %d}\n", x, y, row[y][x * 3], row[y][x * 3 + 1], row[y][x * 3 + 2]);
            }*/
        }
    }
    //puts("------------------\n");
    for (int y = 0; y < image->height; y++){
        for (int x = 0; x < image->width; x++){
            int count1 = 0;
            int count = size * size;
            int red = 0;
            int green = 0;
            int blue = 0;
            for (int y_n = max(0, y - (size / 2)); y_n <= min(image->height - 1, y + (size / 2)); y_n++){
                for (int x_n = max(0, x - (size / 2)); x_n <= min(image->width - 1, x + (size / 2)); x_n++){
                    count1 ++;
                    red += row[y_n][x_n * 3];
                    green += row[y_n][x_n * 3 + 1];
                    blue += row[y_n][x_n * 3 + 2];
                }
            }
            if (count != count1){
                red += (count-count1) * row[y][x*3];
                green += (count-count1) * row[y][x*3+1];
                blue += (count-count1) * row[y][x*3+2];
            }
            red = red / count;
            green = green / count;
            blue = blue / count;
            set_pixel(image, x, y, red, green, blue);
            /*if (x<200 && x>196 && y<200 && y>196){
                printf("%d %d {%d %d %d}\n", x, y, red, green, blue);
            }*/
        }
    }
}


