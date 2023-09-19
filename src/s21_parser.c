#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "s21_3dviewer.h"
#include "s21_parser.h"

int read_data_from_file(const char file_name[], figure_t *figure) {
    FILE *obj_file;
    figure->dots_number = 0; figure->lines_number = 0; figure->triangles_number = 0;
    int error = 0, str_number = 0;
    if ((obj_file = fopen(file_name, "r")) == NULL) {
        error = 1;
    } else {
        figure_t temp_figure;
        int lines_number = number_of_lines_from_file(obj_file);
        fclose(obj_file);
        obj_file = NULL;
        obj_file = fopen(file_name, "r");
        int *lines_lenths;
        lines_lenths = (int*)calloc(lines_number, sizeof(int));
        read_line_lenth(obj_file, lines_lenths);
        fclose(obj_file);
        obj_file = NULL;
        char **strs_from_file = NULL;
        strs_from_file = (char**)calloc(lines_number, sizeof(char *));
        for (int i = 0; i < lines_number; i++) {
            strs_from_file[i] = (char *)calloc(lines_lenths[i], sizeof(char));
            for (int j = 0; j < lines_lenths[i]; j++) strs_from_file[i][j] = '\0';
        }
        obj_file = fopen(file_name, "r");
        read_str_from_file(obj_file, strs_from_file, &str_number);
        fclose(obj_file);
        read_number_of_dots_and_facets_from_str(strs_from_file, str_number, &temp_figure);
        temp_figure.lines_number = temp_figure.triangles_number * 5;
        int temp_lines_amount = temp_figure.lines_number;
        init_figure(&temp_figure);
        read_dots_from_str(strs_from_file, lines_number, &temp_figure);
        read_polygons_from_str(strs_from_file, lines_number, &temp_figure, lines_lenths);
        free(lines_lenths);
        for (int i = 0; i < lines_number; i++) free(strs_from_file[i]);
        free(strs_from_file);
        find_lines_number(&temp_figure);
        copy_figure(figure, &temp_figure);
        temp_figure.lines_number = temp_lines_amount;
        remove_figure(&temp_figure);
    }
    return error;
}

void read_number_of_dots_and_facets_from_str(char **strs_from_file, int str_number, figure_t *figure) {
    figure->dots_number = 0;
    figure->triangles_number = 0;
    for (int i = 0; i < str_number; i++) {
        if (strs_from_file[i][0] == 'v' && strs_from_file[i][1] == ' ' ) figure->dots_number += 1;
        if (strs_from_file[i][0] == 'f' && strs_from_file[i][1] == ' ' ) figure->triangles_number += 1;
    }
}

int number_of_lines_from_file(FILE *obj_file) {
     char letter;
     int str_counter = 0;
     while (!feof(obj_file)) {
         letter = fgetc(obj_file);
         if (letter == 10 || letter == EOF) {
            str_counter++;
         }
     }
     return str_counter;
}


void find_lines_number(figure_t *figure) {
    int counter = 0, counter_2 = 0, hash_amount = figure->triangles_number * TEMP_LINES_NUMBER * 2;
    int **temp_lines, **hash_arr;
    temp_lines = (int **)calloc(figure->triangles_number * TEMP_LINES_NUMBER, sizeof(int*));
    for (int i = 0; i < figure->triangles_number * TEMP_LINES_NUMBER; i++) {
        temp_lines[i] = (int*) calloc(2, sizeof(int)); temp_lines[i][0] = -1; temp_lines[i][1] = -1;
        }
    for (int i = 0; i < figure->triangles_number; i++) {
        int dots_counter = 1;
        while (figure->triangles[i][dots_counter] != -1) {
            temp_lines[counter][0] = figure->triangles[i][dots_counter - 1];
            temp_lines[counter][1] = figure->triangles[i][dots_counter];
            counter++;
            dots_counter++;
        }
        if (figure->triangles[i][dots_counter] == -1) {
            temp_lines[counter][0] = figure->triangles[i][0];
            temp_lines[counter][1] = figure->triangles[i][dots_counter - 1];
            counter++;
        }
    }
    hash_arr = (int**)calloc(hash_amount, sizeof(int*));
    for (int i = 0; i < hash_amount; i++) {
        hash_arr[i] = (int*) calloc(2, sizeof(int)); hash_arr[i][0] = -1; hash_arr[i][1] = -1;
    }
    creat_hash_for_lines_number(temp_lines, counter, hash_arr, hash_amount);
    for (int i = 0; i < hash_amount; i++) {
        if (hash_arr[i][0] != -1 && hash_arr[i][1] != -1) {
            figure->lines[counter_2][0] = hash_arr[i][0];
            figure->lines[counter_2][1] = hash_arr[i][1];
            counter_2++;
        }
    }
    figure->lines_number = counter_2;
    for (int i = 0; i < figure->triangles_number * TEMP_LINES_NUMBER; i++) {
        free(temp_lines[i]);
    }
     free(temp_lines);
    for (int i = 0; i < hash_amount; i++) {
        free(hash_arr[i]);
    }
    free(hash_arr);
}

void creat_hash_for_lines_number(int **temp_lines, int counter, int **hash_arr, int hash_amount) {
    int counter_3 = 0;
    for (int i = 0; i < counter; i++) {
        int max = temp_lines[i][0], min = temp_lines[i][1];
        if (max < min) {
            max = temp_lines[i][1];
            min = temp_lines[i][0];
        }
        unsigned int hash = ((max * 6342) % hash_amount  + min); hash = hash % hash_amount;
        if (hash_arr[hash][0] == -1 && hash_arr[hash][1] == -1) {
            hash_arr[hash][0] = temp_lines[i][0];
            hash_arr[hash][1] = temp_lines[i][1];
            counter_3++;
        } else {
            if (hash_arr[hash][0] == temp_lines[i][0] && hash_arr[hash][1] == temp_lines[i][1]) {
                continue;
            } else if (hash_arr[hash][0] == temp_lines[i][1] && hash_arr[hash][1] == temp_lines[i][0]) {
                continue;
            } else {
                while (hash_arr[hash][0] != -1 && hash_arr[hash][1] != -1) {
                    hash++; hash %= hash_amount;
                    if (hash_arr[hash][0] == temp_lines[i][0] && hash_arr[hash][1] == temp_lines[i][1]) {
                        break;
                    } else if (hash_arr[hash][0] == temp_lines[i][1] && hash_arr[hash][1] == temp_lines[i][0]) {
                        break;
                    } else if (hash_arr[hash][0] == -1 && hash_arr[hash][1] == -1) {
                        hash_arr[hash][0] = temp_lines[i][0];
                        hash_arr[hash][1] = temp_lines[i][1];
                        counter_3++; break;
                    }
                }
            }
        }
    }
}

void print_str_from_file(char **strs_from_file, int str_number) {
    printf("Hello, You are in print_str_from_file function\n");
    for (int i = 0; i < str_number; i++) {
        printf("%s", strs_from_file[i]);
        printf("\n");
    }
    printf("\n");
}

void read_dots_from_str(char **strs_from_file, int str_number, figure_t *figure) {
    int counter = 0;
        for (int i = 0; i < str_number; i++) {
            char letter = 0, str1[20], str2[20], str3[20];
            for (int j = 0; j < 20; j++) {
                str1[j] = '\0';
                str1[j] = '\0';
                str1[j] = '\0';
            }
            if (strs_from_file[i][0] == 'v' && strs_from_file[i][1] == ' ') {
                sscanf((const char *)strs_from_file[i], "%c%s%s%s", &letter, str1, str2, str3);
                figure->dots[counter][0] = convert_str_to_double(str1, strlen(str1));
                figure->dots[counter][1] = convert_str_to_double(str2, strlen(str2));
                figure->dots[counter][2] = convert_str_to_double(str3, strlen(str3));

                figure->dots[counter][3] = 1;
                counter++;
            }
    }
    figure->dots_number = counter;
}

double convert_str_to_double(char number[], int counter) {
    int before_dot_flag = 1, devider = 10, add = 0;
    double multiplyer = 1, rezult;
    if (number[0] == '-') {
        multiplyer = -1;
        rezult = (double)(number[1] - 48);
        add = 1;
    } else {
        rezult = (double)(number[0] - 48);
    }
    for (int i = 1 + add; i < counter; i++) {
        if (number[i] == '.' || number[i] == ',') {
            before_dot_flag = 0;
            continue;
        }
        if (before_dot_flag == 1) {
            rezult = rezult*10 + (double) (number[i] - 48);
        } else {
            rezult = rezult + ((double)(number[i] - 48))/devider;
            devider *= 10;
        }
    }
    rezult *= multiplyer;
    return rezult;
}


void read_polygons_from_str(char **strs_from_file, int str_number, figure_t *figure, int *lines_lenths) {
    int counter = 0, calloc_flag = 0;
    for (int i = 0; i < str_number; i++) {
        if (strs_from_file[i][0] == 'f' && strs_from_file[i][1] == ' ') {
            int counter_of_dots = 0, flag = 0, temp_number = 0, slash_flag = 0;
            for (int j = 1; j < lines_lenths[i]; j++) {
                if (counter_of_dots == DOTS_IN_POLYGON && calloc_flag == 0) {
                    free(figure->triangles[counter]);
                    figure->triangles[counter] = (int*)calloc(200, sizeof(int));
                    for (int k = 0; k < 200; k++) figure->triangles[counter][k] = -1;
                    calloc_flag = 1;
                    i--;
                    counter--;
                    break;
                }
                if (flag == 0 && strs_from_file[i][j] == ' ') {
                    slash_flag = 0;
                }
                if (strs_from_file[i][j] >= '0' && strs_from_file[i][j] <= '9' && flag == 0 && slash_flag == 0) {
                    figure->triangles[counter][counter_of_dots] =strs_from_file[i][j] - 48;
                    temp_number = figure->triangles[counter][counter_of_dots] * 10;
                    flag = 1;
                } else if (strs_from_file[i][j] >= '0' && strs_from_file[i][j] <= '9' && flag == 1 && slash_flag == 0) {
                    figure->triangles[counter][counter_of_dots] = temp_number + strs_from_file[i][j] - 48;
                    temp_number = figure->triangles[counter][counter_of_dots] * 10;
                } else if (strs_from_file[i][j] == '/' && flag == 1 && slash_flag == 0) {
                    slash_flag = 1;
                } else if (flag == 1 && (slash_flag == 1 || strs_from_file[i][j] >= ' ' || strs_from_file[i][j] >= '\0')) {
                    flag = 0;
                    figure->triangles[counter][counter_of_dots] -= 1;
                    counter_of_dots++;
                    if (counter_of_dots > DOTS_IN_POLYGON && calloc_flag == 1) {
                        calloc_flag = 0;
                    }
                }
            }
            counter++;
        }
    }
    figure->triangles_number = counter;
}



void read_str_from_file(FILE *obj_file, char **strs_from_file, int *str_number) {
     char letter;
     int counter = 0;
     while (!feof(obj_file)) {
         letter = fgetc(obj_file);
         if (letter == 10 || letter == EOF) {
            if (letter == EOF) {
                strs_from_file[*str_number][counter] = '\0';
            } else {
                strs_from_file[*str_number][counter] = '\0';
            }
            counter = 0;
            *str_number = *str_number + 1;
         } else {
            strs_from_file[*str_number][counter] = letter;
            counter++;
         }
     }
}


void read_line_lenth(FILE *obj_file, int *line_lenths) {
    int counter = 0, line_counter = 0;
    char letter;
         while (!feof(obj_file)) {
         letter = fgetc(obj_file);
         if (letter == 10 || letter == EOF) {
            counter++;
            counter++;
            line_lenths[line_counter] = counter;
            counter = 0;
            line_counter++;
         } else {
            counter++;
         }
     }
}
