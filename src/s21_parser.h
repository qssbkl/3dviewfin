#ifndef SRC_S21_PARSER_H_
#define SRC_S21_PARSER_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "s21_3dviewer.h"

#define STR_NUMBER 15000
#define LINE_LENTH 2000
#define TEMP_LINES_NUMBER 5


int read_data_from_file(const char file_name[], figure_t *figure);
void read_number_of_dots_and_facets_from_str(char **strs_from_file, int str_number, figure_t *temp_figure);
int number_of_lines_from_file(FILE *obj_file);
// void make_lines_set(figure_t *figure);
void find_lines_number(figure_t *figure);
void creat_hash_for_lines_number(int **temp_lines, int counter, int **hesh_arr, int hash_amount);
void print_str_from_file(char **strs_from_file, int str_number);
void read_dots_from_str(char **strs_from_file, int str_number, figure_t *figure);
double convert_str_to_double(char number[], int counter);
void read_polygons_from_str(char **strs_from_file, int str_number, figure_t *figure, int *lines_lenths);
void read_str_from_file(FILE *obj_file, char **strs_from_file, int *str_number);
void read_line_lenth(FILE *obj_file, int *line_lenths);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_PARSER_H_
