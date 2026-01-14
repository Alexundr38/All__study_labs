#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "png_process.h"


typedef struct Data{
    int circle;
    int filter;
    int split;
    int x_center, y_center;
    int radius;
    int thikness;
    int red, green, blue;
    int fill;
    int fill_red, fill_green, fill_blue;
    char *component_name;
    int component_value;
    int number_x, number_y;
} Data;

int main(int argc, char **argv){

    puts("Course work for option 4.23, created by Rudakov Aleksandr");

    if (argc == 1){
        puts("Error: no flags");
        exit(40);
    }
    
    int opt;
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"input", required_argument, 0, 'i'},
        {"output", required_argument, 0 ,'o'},
        {"info", no_argument, 0, 'f'},
        {"circle", no_argument, 0, 'c'},
        {"rgbfilter", no_argument, 0, 'r'},
        {"split", no_argument, 0, 's'},
        {"center", required_argument, 0, 'C'},
        {"radius", required_argument, 0, 'R'},
        {"thickness", required_argument, 0, 'T'},
        {"color", required_argument, 0, 'L'},
        {"fill", no_argument, 0, 'F'},
        {"fill_color", required_argument, 0, 'O'},
        {"component_name", required_argument , 0, 'N'},
        {"component_value", required_argument, 0, 'V'},
        {"number_x", required_argument, 0, 'X'},
        {"number_y", required_argument, 0, 'Y'},
        {"contrast", no_argument, 0, 'S'},
        {"alpha", required_argument, 0, 'A'},
        {"beta", required_argument, 0, 'B'},
        {"blur", no_argument, 0, 'b'},
        {"size", required_argument, 0, 'z'}
    };

    Data data;
    data.circle = 0;
    data.filter = 0;
    data.split = 0;
    data.x_center = 0;
    data.y_center = 0;
    data.radius = 0;
    data.thikness = 0;
    data.red = -1;
    data.green = -1;
    data.blue = -1;
    data.fill = 0;
    data.fill_red = -1;
    data.fill_green = -1;
    data.fill_blue = -1;
    data.component_value = -1;
    data.number_x = 0;
    data.number_y = 0;

    char digit[] = "0123456789";
    int count_circle = 0;
    int count_filter = 0;
    int count_split = 0;
    int help_flag = 0;
    int info_flag = 0;
    double alpha = 0;
    int beta = 0;
    int contrast = 0;
    int blur = 0;
    int size = 0;

    char *input = NULL;
    char *output = NULL;

    while ((opt = getopt_long(argc, argv, "i:o:crfC:R:T:L:FO:N:V:X:Y:", long_options, NULL)) != -1){
        switch(opt){
            case 'h':
                puts(
                    "Error 40 - incorrect flags\n"
                    "Error 41 - incorrect arguments\n"
                    "Error 42 - the problem of working with image\n"
                    "Error 43 - incorrect file\n"
                    "\n"
                    "Flags:\n"
                    "--input - set the name of the input image\n"
                    "--output - set the name of the output image\n"
                    "--info - print information about the image\n"
                    "--help - display the help\n"
                    "--circle - draw a circle, defined by flags:\n\t--center x.y\n\t--radius r\n"
                    "\t--thikness thik\n\t--color r.g.b\n\t--fill\n\t--fill_color\n\tr.g.b\n"
                    "--rgbfilter - set the rgb-component value for the entire image, defined by flags:\n"
                    "\t--component_name name\n\t--component_value val\n"
                    "--split - divide the image into N*M parts, defined by flags:\n"
                    "\t--number_x n_x\n\t--number_y n_y\n\t--thikness thik\n\t--color r.g.b"
                );
                help_flag = 1;
                exit(0);


            case 'i':
                input = (char*)malloc(sizeof(char) * (strlen(optarg) + 1));
                strncpy(input, optarg, strlen(optarg));
                input[strlen(optarg)] = '\0';
                break;


            case 'o':
                output = (char*)malloc(sizeof(char) * (strlen(optarg) + 1));
                strncpy(output, optarg, strlen(optarg));
                output[strlen(optarg)] = '\0';
                break;
            

            case 'f':
                info_flag = 1;
                break;

            case 'c':
                data.circle = 1;
                break;


            case 'r':
                data.filter = 1;
                break;


            case 's':
                data.split = 1;
                break;


            case 'C':
                if (sscanf(optarg, "%d.%d", &data.x_center, &data.y_center) == 2){
                    char* dot = strstr(optarg, ".");
                    int add = 1;
                    if (*(dot + 1) == '-'){
                        add = 2;
                    }
                    if (strlen(optarg) == ((dot + strspn(dot + add, digit) + add) - optarg)){           //correct center
                        count_circle++;
                        break;
                    } else {                                                                            //incorrect center
                        puts("Error: incorrect arguments");
                        exit(41);
                    }
                } else {                                                                                //incorrect center
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'R':
                if (sscanf(optarg, "%d", &data.radius) == 1){
                    if (strlen(optarg) == strspn(optarg, digit)){
                        if (data.radius > 0){                                                           //correcr radius
                            count_circle++;
                            break;
                        } else{                                                                         //radius <= 0
                            puts("Error: radius must be greater than 0");  
                            exit(41);
                        }
                    } else {                                                                            //incorrect radius
                        puts("Error: incorrect arguments");
                        exit(41);
                    }
                } else {                                                                                //incorrect radius
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'T':
                if (sscanf(optarg, "%d", &data.thikness) == 1){
                    if (strlen(optarg) == strspn(optarg, digit)){
                        if (data.thikness >0){                                                          //correct thikness
                            count_circle++;
                            count_split++;
                            break;
                        }
                        else{                                                                           //thikness <= 0
                            puts("Error: thikness must be greater than -1");
                            exit(41);
                        }
                    } else{                                                                             //incorrect thikness
                        puts("Error: incorrect arguments");
                        exit(41);
                    }
                } else{                                                                                 //incorrect thikness
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'L':
                if (sscanf(optarg, "%d.%d.%d", &data.red, &data.green, &data.blue) == 3){
                    char *first_dot = strstr(optarg, ".") + 1;
                    char *second_dot = strstr(first_dot, ".") + 1;
                    if (strlen(optarg) == (strspn(optarg, digit) + strspn(first_dot, digit) + \
                        strspn(second_dot, digit) + 2)){
                            if (data.red >= 0 && data.green >= 0 && data.blue >= 0 \
                                && data.red < 256 && data.green < 256 && data.blue < 256){              //correct color
                                    count_circle++;
                                    count_split++;
                            } else {                                                                    //incorrect color
                                puts("Error: rgb components must be greatest than 0 and less than 256");                                              //components of color < 0
                                exit(41);
                            }
                    } else {                                                                            //incorrect color
                        puts("Error: incorrect arguments");
                        exit(41);
                    }
                } else {                                                                                //incorrect color
                    puts("Error: incorrect arguments");
                    exit(41);
                }

                break;


            case 'F':
                data.fill = 1;

                count_circle++;
                break;


            case 'O':
                if (sscanf(optarg, "%d.%d.%d", &data.fill_red, &data.fill_green, &data.fill_blue) == 3){
                    char *first_dot = strstr(optarg, ".") + 1;
                    char *second_dot = strstr(first_dot, ".") + 1;
                    if (strlen(optarg) == (strspn(optarg, digit) + strspn(first_dot, digit) + \
                        strspn(second_dot, digit) + 2)){
                            if (data.fill_red >= 0 && data.fill_green >= 0 && data.fill_blue >= 0 \
                                && data.fill_red < 256 && data.fill_green < 256 && data.fill_blue < 256){   //correct color_fill     
                                    count_circle++;
                                    break;
                            } else {                                                                    //incorrect color_fill
                                puts("Error: rgb components must be greatest than 0 and less than 256");                                              //components of color < 0
                                exit(41);
                            }
                    } else {                                                                            //incorrect color_fill
                        puts("Error: incorrect arguments");
                        exit(41);
                    }
                } else {                                                                                //incorrect color_fill
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'N':
                count_filter++;

                if (!strcmp(optarg, "red")){                                                                 //correct component_name
                    data.component_name = (char*)malloc(sizeof(char) * 4);
                    strncpy(data.component_name, optarg, 3);
                    data.component_name[3] = '\0';
                    break;
                } else if (!strcmp(optarg, "green")){                                                        //correct component_name
                    data.component_name = (char*)malloc(sizeof(char) * 6);
                    strncpy(data.component_name, optarg, 5);
                    data.component_name[5] = '\0';
                    break;
                } else if (!strcmp(optarg, "blue")){                                                         //correct component_name
                    data.component_name = (char*)malloc(sizeof(char) * 5);
                    strncpy(data.component_name, optarg, 4);
                    data.component_name[4] = '\0';
                    break;
                } else {                                                                                     //incorrect component_name
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'V':
                if (sscanf(optarg, "%d", &data.component_value) == 1){
                    if (data.component_value >= 0 && data.component_value < 256){
                        if (strlen(optarg) == strspn(optarg, digit)){                                       //correct component_value
                            count_filter++;
                            break;
                        } else {                                                                            //incorrect component_value
                            puts("Error: incorrect arguments");
                            exit(41);
                        }
                    } else {                                                                                //incorrect component_value
                        puts("Error: component_value must be greater than -1 and less than 256");
                        exit(41);
                    }
                } else {                                                                                    //incorrect component_value
                    puts("Error: incorrect arguments");
                    exit(41);
                }

                
            case 'X':
                if (sscanf(optarg, "%d", &data.number_x) == 1){
                    if (strlen(optarg) == strspn(optarg, digit)){  
                        if (data.number_x > 0){                                                             //correct number_x
                            count_split++;
                            break;
                        } else {                                                                            //incorrect number_x
                            puts("Error: number_x must be greater then 0");
                            exit(41);
                        }
                    } else {                                                                                //incorrect number_x 
                        puts("Error: incorrect argument");
                        exit(41);
                    }
                } else{                                                                                     //incorrect number_x
                    puts("Error: incorrect arguments");
                    exit(41);
                }


            case 'Y':
                if (sscanf(optarg, "%d", &data.number_y) == 1){
                    if (strlen(optarg) == strspn(optarg, digit)){  
                        if (data.number_y > 0){                                                             //correct number_y
                            count_split++;
                            break;
                        } else {                                                                            //incorrect number_y
                            puts("Error: number_y must be greater then 0");
                            exit(41);
                        }
                    } else {                                                                                //incorrect number_y 
                        puts("Error: incorrect argument");
                        exit(41);
                    }
                } else{                                                                                     //incorrect number_y
                    puts("Error: incorrect arguments");
                    exit(41);
                } 


            case 'S':
                contrast = 1;
                break;


            case 'A':
                sscanf(optarg, "%lf", &alpha);
                break;

            
            case 'B':
                sscanf(optarg, "%d", &beta);
                break;

            
            case 'b':
                blur = 1;
                break;


            case 'z':
                sscanf(optarg, "%d", &size);
                break;


            default:
                puts("Error: incorrect flags");                                                             //incorrect flag
                exit(40);
        }
    }

    png image;
    read_png(input, &image);

    if (info_flag == 1){
        inf(&image);
        exit(0);
    }

    if (data.circle == 1 && !((data.fill == 0 && (count_circle == 4 || count_circle == 5)) || (data.fill == 1 && count_circle == 6))){ //few flags
        puts("Error: few flags have been intoduced");
        exit(40);
    }
    if (data.filter == 1 && count_filter != 2){                                                             //few flags
        puts("Error: few flags have been intoduced");
        exit(40);
    }
    if (data.split == 1 && count_split != 4){                                                               //few flags
        puts("Error: few flags have been intoduced");
        exit(40);
    }
    if (data.circle + data.filter + data.split + contrast + blur > 1){                                                        //too many flags
        puts("Error: there are too many flags");
        exit(40);
    }
    if (data.circle + data.filter + data.split + contrast + blur == 0){
        puts("Error: few flags have been intoduced");
        exit(40);
    }

    if (data.circle == 1){
        circle(&image, data.x_center, data.y_center, data.radius, data.thikness, data.red, \
            data.green, data.blue, data.fill, data.fill_red, data.fill_green, data.fill_blue);
    }

    if (data.filter == 1){
        rgb_filter(&image, data.component_name, data.component_value);
    }

    if (data.split == 1){
        rgb_split(&image, data.number_x, data.number_y, data.thikness, data.red, data.green, data.blue);
    }

    if (contrast == 1){
        rgb_contrast(&image, alpha, beta);
    }
    
    if (blur == 1){
        rgb_blur(&image, size);
    }

    if (help_flag == 0){
        write_png(output, &image);
    }

    for (int y = 0; y < image.height; y++)
         free(image.row_pointers[y]);
    free(image.row_pointers);
}
