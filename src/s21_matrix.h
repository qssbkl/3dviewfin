#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_transpose(matrix_t *A);
matrix_t s21_calc_complements(matrix_t *A);
double s21_determinant(matrix_t *A);
matrix_t s21_inverse_matrix(matrix_t *A);

void s21_print_matrix(matrix_t *A);
int s21_check_matrix_for_no_mistakes(matrix_t *A);
void s21_matrix_type_check_for_correct_zero_and_identity(matrix_t *A);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_MATRIX_H_
