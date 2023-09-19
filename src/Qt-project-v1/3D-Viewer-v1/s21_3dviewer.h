#ifndef SRC_MULTI_MOVE_TRAINING_S21_3DVIEWER_H_
#define SRC_MULTI_MOVE_TRAINING_S21_3DVIEWER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "s21_matrix.h"

#define DOTS 3000
#define TRIANGLES 6000
#define LINES 12000
#define S21_PI 3.1415926535
#define DOTS_IN_POLYGON 5

typedef struct figure_struct {
    int dots_number;
    double **dots;
    int triangles_number;
    int **triangles;
    int lines_number;
    int **lines;
} figure_t;

void init_figure(figure_t *figure);
void creat_cube(figure_t *figure);
void print_figure(figure_t *figure);
void remove_figure(figure_t *figure);
void copy_figure(figure_t *dist_figure, figure_t *src_figure);
matrix_t transform_matrix(double x, double y, double z);
matrix_t move_matrix(double x, double y, double z);
matrix_t resize_matrix(double x, double y, double z);
matrix_t rotation_matrix(double alfa);
matrix_t rotation_matrix(double betta);
matrix_t z_rotation_matrix(double gamma);
void copy_to_matrix(matrix_t *matrix, figure_t *figure, int number);
void copy_from_matrix(figure_t *figure, matrix_t *matrix, int number);
void copy_figure_to_matrix(matrix_t *matrix, figure_t *figure);
void copy_figure_from_matrix(figure_t *figure, matrix_t *matrix);
void move_figure(figure_t *figure, double x, double y, double z);
void resize_figure(figure_t *figure, double x, double y, double z);
void rotate_figure(figure_t *figure, double alfa, double betta, double gamma);
void transform_figure(figure_t *figure, double x, double y, double z);
void multi_move(figure_t *figure, double x_move, double y_move, double z_move,
                double x_resize, double y_resize, double z_resize,
                double alfa, double betta, double gamma,
                double x_transform, double y_transform, double z_transform);

#ifdef __cplusplus
}
#endif

#endif  // SRC_MULTI_MOVE_TRAINING_S21_3DVIEWER_H_
