#include "s21_3dviewer.h"


void init_figure(figure_t *figure) {
    if (figure->dots_number > 2000000) figure->dots_number = 2000000;
    if (figure->dots_number < 0) figure->dots_number = 1;
    figure->dots = (double **)calloc(figure->dots_number, sizeof(double*));
    for (int i = 0; i < figure->dots_number; i++) {
        figure->dots[i] = (double*)calloc(4, sizeof(double));
        figure->dots[i][0] = 0;
        figure->dots[i][1] = 0;
        figure->dots[i][2] = 0;
        figure->dots[i][3] = 1;
    }
    if (figure->triangles_number > 4500000) figure->triangles_number = 4500000;
    if (figure->triangles_number < 0) figure->triangles_number = 1;
    figure->triangles = (int **)calloc(figure->triangles_number, sizeof(int*));
    for (int i = 0; i < figure->triangles_number; i++) {
        figure->triangles[i] = (int*)calloc(DOTS_IN_POLYGON, sizeof(int));
        for (int j = 0; j < DOTS_IN_POLYGON; j++) {
            figure->triangles[i][j] = -1;
        }
    }
    if (figure->lines_number > 9000000) figure->lines_number = 9000000;
    if (figure->lines_number < 0) figure->lines_number = 1;
    figure->lines = (int **)calloc(figure->lines_number, sizeof(int*));
    for (int i = 0; i < figure->lines_number; i++) {
        figure->lines[i] = (int*)calloc(2, sizeof(int));
        figure->lines[i][0] = 0;
        figure->lines[i][1] = 0;
    }
}

void remove_figure(figure_t *figure) {
    if (figure->dots_number != 0) {
        for (int i = 0; i < figure->dots_number; i++) {
            free(figure->dots[i]);
        }
        free(figure->dots);
    } else {
        figure->dots_number = 0;
    }
    if (figure->triangles_number != 0) {
        for (int i = 0; i < figure->triangles_number; i++) {
            free(figure->triangles[i]);
        }
        free(figure->triangles);
    } else {
        figure->triangles_number = 0;
        }
    if (figure->lines_number != 0) {
        for (int i = 0; i < figure->lines_number; i++) {
            free(figure->lines[i]);
        }
        free(figure->lines);
    } else {
        figure->lines_number = 0;
    }
}

void creat_cube(figure_t *figure) {
    figure->dots_number = 8;
    figure->triangles_number = 12;
    figure->lines_number = 18;
    init_figure(figure);
    figure->dots[0][0] = -100;figure->dots[0][1] = 100;figure->dots[0][2] = 100;
    figure->dots[1][0] = -100;figure->dots[1][1] = 100;figure->dots[1][2] = -100;
    figure->dots[2][0] = -100;figure->dots[2][1] = -100;figure->dots[2][2] = -100;
    figure->dots[3][0] = -100;figure->dots[3][1] = -100;figure->dots[3][2] = 100;
    figure->dots[4][0] = 100;figure->dots[4][1] = 100;figure->dots[4][2] = 100;
    figure->dots[5][0] = 100;figure->dots[5][1] = 100;figure->dots[5][2] = -100;
    figure->dots[6][0] = 100;figure->dots[6][1] = -100;figure->dots[6][2] = -100;
    figure->dots[7][0] = 100;figure->dots[7][1] = -100;figure->dots[7][2] = 100;
    figure->triangles[0][0] = 0;figure->triangles[0][1] = 1;figure->triangles[0][2] = 2;figure->triangles[0][3] = -1;
    figure->triangles[1][0] = 0;figure->triangles[1][1] = 2;figure->triangles[1][2] = 3;figure->triangles[1][3] = -1;
    figure->triangles[2][0] = 1;figure->triangles[2][1] = 2;figure->triangles[2][2] = 6;figure->triangles[2][3] = -1;
    figure->triangles[3][0] = 1;figure->triangles[3][1] = 6;figure->triangles[3][2] = 5;figure->triangles[3][3] = -1;
    figure->triangles[4][0] = 5;figure->triangles[4][1] = 6;figure->triangles[4][2] = 7;figure->triangles[4][3] = -1;
    figure->triangles[5][0] = 5;figure->triangles[5][1] = 7;figure->triangles[5][2] = 4;figure->triangles[5][3] = -1;
    figure->triangles[6][0] = 0;figure->triangles[6][1] = 4;figure->triangles[6][2] = 7;figure->triangles[6][3] = -1;
    figure->triangles[7][0] = 0;figure->triangles[7][1] = 7;figure->triangles[7][2] = 3;figure->triangles[7][3] = -1;
    figure->triangles[8][0] = 0;figure->triangles[8][1] = 1;figure->triangles[8][2] = 5;figure->triangles[8][3] = -1;
    figure->triangles[9][0] = 0;figure->triangles[9][1] = 5;figure->triangles[9][2] = 4;figure->triangles[9][3] = -1;
    figure->triangles[10][0] = 3;figure->triangles[10][1] = 2;figure->triangles[10][2] = 6;figure->triangles[10][3] = -1;
    figure->triangles[11][0] = 3;figure->triangles[11][1] = 6;figure->triangles[11][2] = 7;figure->triangles[11][3] = -1;
    figure->lines[0][0] = 0; figure->lines[0][1] = 1;
    figure->lines[1][0] = 1; figure->lines[1][1] = 2;
    figure->lines[2][0] = 2; figure->lines[2][1] = 3;
    figure->lines[3][0] = 3; figure->lines[3][1] = 0;
    figure->lines[4][0] = 0; figure->lines[4][1] = 2;
    figure->lines[5][0] = 4; figure->lines[5][1] = 5;
    figure->lines[6][0] = 5; figure->lines[6][1] = 6;
    figure->lines[7][0] = 6; figure->lines[7][1] = 7;
    figure->lines[8][0] = 7; figure->lines[8][1] = 4;
    figure->lines[9][0] = 4; figure->lines[9][1] = 6;
    figure->lines[10][0] = 0; figure->lines[10][1] = 4;
    figure->lines[11][0] = 1; figure->lines[11][1] = 5;
    figure->lines[12][0] = 2; figure->lines[12][1] = 6;
    figure->lines[13][0] = 3; figure->lines[13][1] = 7;
    figure->lines[14][0] = 0; figure->lines[14][1] = 5;
    figure->lines[15][0] = 1; figure->lines[15][1] = 6;
    figure->lines[16][0] = 2; figure->lines[16][1] = 7;
    figure->lines[17][0] = 3; figure->lines[17][1] = 4;
}

void print_figure(figure_t *figure) {
    for (int i = 0; i < figure->dots_number; i++) {
        printf("figure->dots[%2d][0] = %+4.0f", i, figure->dots[i][0]);
        printf("  figure->dots[%2d][1] = %+4.0f", i, figure->dots[i][1]);
        printf("  figure->dots[%2d][2] = %+4.0f\n", i, figure->dots[i][2]);
    }
    
    for (int i = 0; i < figure->triangles_number; i++) {
        int counter = 0;
        while (figure->triangles[i][counter] != -1) {
            printf("fig->trg[%2d][0] = %2d ", i, figure->triangles[i][counter]);
            counter++;
        }
         printf("fig->trg[%2d][0] = %2d\n", i, figure->triangles[i][counter]);
    }
    printf("\n");
    for (int i = 0; i < figure->lines_number; i++) {
        printf("figure->lines[%2d][0] = %2d", i, figure->lines[i][0]);
        printf("  figure->lines[%2d][1] = %2d\n", i, figure->lines[i][1]);
    }
    printf("figure->dots_number %d\n", figure->dots_number);
    printf("figure->triangles_number %d\n", figure->triangles_number);
    printf("figure->lines_number %d\n", figure->lines_number);
}

void copy_figure(figure_t *dist_figure, figure_t *src_figure) {
    dist_figure->dots_number = src_figure->dots_number;
    dist_figure->triangles_number = src_figure->triangles_number;
    dist_figure->lines_number = src_figure->lines_number;
    init_figure(dist_figure);
    for (int i = 0; i < src_figure->dots_number; i++) {
        dist_figure->dots[i][0] = src_figure->dots[i][0];
        dist_figure->dots[i][1] = src_figure->dots[i][1];
        dist_figure->dots[i][2] = src_figure->dots[i][2];
        dist_figure->dots[i][3] = src_figure->dots[i][3];
    }
    for (int i = 0; i < src_figure->triangles_number; i++) {
        dist_figure->triangles[i][0] = src_figure->triangles[i][0];
        dist_figure->triangles[i][1] = src_figure->triangles[i][1];
        dist_figure->triangles[i][2] = src_figure->triangles[i][2];
        dist_figure->triangles[i][3] = src_figure->triangles[i][3];
    }
    for (int i = 0; i < src_figure->lines_number; i++) {
        dist_figure->lines[i][0] = src_figure->lines[i][0];
        dist_figure->lines[i][1] = src_figure->lines[i][1];
    }
}

matrix_t transform_matrix(double x, double y, double z) {
    matrix_t matrix = s21_create_matrix(4, 4);
    for (int i = 0; i < matrix.rows; ++i) {
        matrix.matrix[i][i] = 1;
    }
    matrix.matrix[3][0] = x;
    matrix.matrix[3][1] = y;
    matrix.matrix[3][2] = z;
    matrix.matrix_type = CORRECT_MATRIX;
    return matrix;
}

matrix_t move_matrix(double x, double y, double z) {
    matrix_t matrix = s21_create_matrix(4, 4);
    for (int i = 0; i < matrix.rows; ++i) {
        matrix.matrix[i][i] = 1;
    }
    matrix.matrix[0][3] = x;
    matrix.matrix[1][3] = y;
    matrix.matrix[2][3] = z;
    matrix.matrix_type = CORRECT_MATRIX;
    return matrix;
}

matrix_t resize_matrix(double x, double y, double z) {
    matrix_t matrix = s21_create_matrix(4, 4);
    matrix.matrix[0][0] = x;
    matrix.matrix[1][1] = y;
    matrix.matrix[2][2] = z;
    matrix.matrix[3][3] = 1;
    matrix.matrix_type = CORRECT_MATRIX;
    return matrix;
}
matrix_t x_rotation_matrix(double alfa) {
    matrix_t matrix = s21_create_matrix(4, 4);
    alfa = (alfa * S21_PI) / 180;
    matrix.matrix[0][0] = 1;
    matrix.matrix[1][1] = cos(alfa);
    matrix.matrix[1][2] = sin(alfa);
    matrix.matrix[2][2] = cos(alfa);
    matrix.matrix[2][1] = -sin(alfa);
    matrix.matrix[3][3] = 1;
    return matrix;
}
matrix_t y_rotation_matrix(double betta) {
    matrix_t matrix = s21_create_matrix(4, 4);
    betta = (betta * S21_PI) / 180;
    matrix.matrix[0][0] = cos(betta);
    matrix.matrix[1][1] = 1;
    matrix.matrix[0][2] = -1 * sin(betta);
    matrix.matrix[2][2] = cos(betta);
    matrix.matrix[2][0] = sin(betta);
    matrix.matrix[3][3] = 1;
    return matrix;
}
matrix_t z_rotation_matrix(double gamma) {
    matrix_t matrix = s21_create_matrix(4, 4);
    gamma = (gamma * S21_PI) / 180;
    matrix.matrix[0][0] = cos(gamma);
    matrix.matrix[1][1] = cos(gamma);
    matrix.matrix[0][1] = sin(gamma);
    matrix.matrix[2][2] = 1;
    matrix.matrix[1][0] = -1 * sin(gamma);
    matrix.matrix[3][3] = 1;
    return matrix;
}

void copy_figure_to_matrix(matrix_t *matrix, figure_t *figure) {
    for (int i = 0; i < figure->dots_number; i++) {
        matrix->matrix[0][i] = figure->dots[i][0];
        matrix->matrix[1][i] = figure->dots[i][1];
        matrix->matrix[2][i] = figure->dots[i][2];
        matrix->matrix[3][i] = figure->dots[i][3];
    }
    matrix->matrix_type = CORRECT_MATRIX;
}

void copy_figure_from_matrix(figure_t *figure, matrix_t *matrix) {
    for (int i = 0; i < figure->dots_number; i++) {
        figure->dots[i][0] = matrix->matrix[0][i];
        figure->dots[i][1] = matrix->matrix[1][i];
        figure->dots[i][2] = matrix->matrix[2][i];
        figure->dots[i][3] = matrix->matrix[3][i];
    }
}


void move_figure(figure_t *figure, double x, double y, double z) {
    matrix_t matrix = move_matrix(x, y, z);
    matrix_t temp = s21_create_matrix(4, figure->dots_number);
    temp.matrix_type = CORRECT_MATRIX;
    matrix_t final;  
    copy_figure_to_matrix(&temp, figure);
    final = s21_mult_matrix(&matrix, &temp);
    copy_figure_from_matrix(figure, &final);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&temp);
    s21_remove_matrix(&final);
}

void resize_figure(figure_t *figure, double x, double y, double z) {
    matrix_t matrix = resize_matrix(x, y, z);
    matrix_t temp = s21_create_matrix(4, figure->dots_number);
    temp.matrix_type = CORRECT_MATRIX;
    matrix_t final;  
    copy_figure_to_matrix(&temp, figure);
    final = s21_mult_matrix(&matrix, &temp);
    copy_figure_from_matrix(figure, &final);
    s21_remove_matrix(&matrix);
    s21_remove_matrix(&temp);
    s21_remove_matrix(&final);
}

void rotate_figure(figure_t *figure, double alfa, double betta, double gamma) {
    matrix_t x_matrix = x_rotation_matrix(alfa);
    matrix_t y_matrix = y_rotation_matrix(betta);
    matrix_t z_matrix = z_rotation_matrix(gamma);
    matrix_t temp_res = s21_mult_matrix(&x_matrix, &y_matrix);
    matrix_t res = s21_mult_matrix(&temp_res, &z_matrix);
    matrix_t temp = s21_create_matrix(4, figure->dots_number);
    temp.matrix_type = CORRECT_MATRIX;
    matrix_t final;  
    copy_figure_to_matrix(&temp, figure);
    final = s21_mult_matrix(&res, &temp);
    copy_figure_from_matrix(figure, &final);
    s21_remove_matrix(&x_matrix);
    s21_remove_matrix(&y_matrix);
    s21_remove_matrix(&z_matrix);
    s21_remove_matrix(&temp_res);
    s21_remove_matrix(&res);
    s21_remove_matrix(&final);
    s21_remove_matrix(&temp);
}

void transform_figure(figure_t *figure, double x, double y, double z) {
    matrix_t temp = s21_create_matrix(4, figure->dots_number);
    matrix_t final;  
    temp.matrix_type = CORRECT_MATRIX;
    copy_figure_to_matrix(&temp, figure);
    matrix_t res = transform_matrix(x, y, z);
    final = s21_mult_matrix(&res, &temp);

    for (int i = 0; i < figure->dots_number; i++) {
        final.matrix[0][i] = final.matrix[0][i] * (2000 + final.matrix[3][i]) / 2000;
        final.matrix[1][i] = final.matrix[1][i] * (2000 + final.matrix[3][i]) / 2000;
        final.matrix[2][i] = final.matrix[2][i] * (2000 + final.matrix[3][i]) / 2000;
        final.matrix[3][i] = 1;
    }
    copy_figure_from_matrix(figure, &final);
    s21_remove_matrix(&final);
    s21_remove_matrix(&temp);
    s21_remove_matrix(&res);
}

void multi_move(figure_t *figure, double x_move, double y_move, double z_move,
                double x_resize, double y_resize, double z_resize,
                double alfa, double betta, double gamma,
                double x_transform, double y_transform, double z_transform) {

    matrix_t matrix_move = move_matrix(x_move, y_move, z_move);
    matrix_t matrix_resize = resize_matrix(x_resize, y_resize, z_resize);
    matrix_t x_matrix = x_rotation_matrix(alfa);
    matrix_t y_matrix = y_rotation_matrix(betta);
    matrix_t z_matrix = z_rotation_matrix(gamma);
    matrix_t temp_res = s21_mult_matrix(&x_matrix, &y_matrix);
    matrix_t matrix_rotate = s21_mult_matrix(&temp_res, &z_matrix);
    matrix_t matrix_transform = transform_matrix(x_transform, y_transform, z_transform);
    matrix_t matrix_move_and_resize = s21_mult_matrix(&matrix_move, &matrix_resize);
    matrix_t matrix_move_resize_rotate = s21_mult_matrix(&matrix_move_and_resize, &matrix_rotate);
    matrix_t matrix_move_resize_rotate_transform = s21_mult_matrix(&matrix_move_resize_rotate, &matrix_transform);
    matrix_t temp = s21_create_matrix(4, figure->dots_number);
    temp.matrix_type = CORRECT_MATRIX;
    copy_figure_to_matrix(&temp, figure);
    matrix_t final = s21_mult_matrix(&matrix_move_resize_rotate_transform, &temp);

    for (int i = 0; i < figure->dots_number; i++) {
        final.matrix[0][i] = final.matrix[0][i] * (1000 + final.matrix[3][i]) / 1000;
        final.matrix[1][i] = final.matrix[1][i] * (1000 + final.matrix[3][i]) / 1000;
        final.matrix[2][i] = final.matrix[2][i] * (1000 + final.matrix[3][i]) / 1000;
        final.matrix[3][i] = 1;
    }

    copy_figure_from_matrix(figure, &final);
    s21_remove_matrix(&matrix_move);
    s21_remove_matrix(&matrix_resize);
    s21_remove_matrix(&x_matrix);
    s21_remove_matrix(&y_matrix);
    s21_remove_matrix(&z_matrix);
    s21_remove_matrix(&temp_res);
    s21_remove_matrix(&matrix_rotate);
    s21_remove_matrix(&matrix_transform);
    s21_remove_matrix(&matrix_move_and_resize);
    s21_remove_matrix(&matrix_move_resize_rotate);
    s21_remove_matrix(&matrix_move_resize_rotate_transform);
    s21_remove_matrix(&temp);
    s21_remove_matrix(&final);
}
