#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <check.h>
#include "s21_3dviewer.h"
#include "s21_parser.h"


START_TEST(s21_matrix_sum_test) {
    matrix_t A = s21_create_matrix(2, 4), B = s21_create_matrix(2, 4), C = s21_create_matrix(2, 4);
    A.matrix[0][0] = 1; A.matrix[0][1] = 2; A.matrix[0][2] = 3; A.matrix[0][3] = 4;
    A.matrix[1][0] = 1; A.matrix[1][1] = 2; A.matrix[1][2] = 3; A.matrix[1][3] = 4;
    A.matrix_type = 0;
    B.matrix[0][0] = 1; B.matrix[0][1] = 2; B.matrix[0][2] = 3; B.matrix[0][3] = 4;
    B.matrix[1][0] = 1; B.matrix[1][1] = 2; B.matrix[1][2] = 3; B.matrix[1][3] = 4;
    B.matrix_type = 0;
    C.matrix[0][0] = 2; C.matrix[0][1] = 4; C.matrix[0][2] = 6; C.matrix[0][3] = 8;
    C.matrix[1][0] = 2; C.matrix[1][1] = 4; C.matrix[1][2] = 6; C.matrix[1][3] = 8;
    C.matrix_type = 0;
    matrix_t D = s21_sum_matrix(&A, &B);
    int answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(1, 1);
    A.matrix_type = 0;
    A.matrix[0][0] = 1;
    B = s21_create_matrix(1, 2);
    B.matrix_type = 0;
    B.matrix[0][0] = 0.01; B.matrix[0][1] = 3;
    C = s21_create_matrix(1, 1);
    C.matrix_type = 0;
    C.matrix[0][0] = 1.01;
    D = s21_sum_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(1, 1);
    A.matrix_type = 1;
    A.matrix[0][0] = 1;
    B = s21_create_matrix(1, 1);
    B.matrix_type = 0;
    B.matrix[0][0] = 0.01;
    C = s21_create_matrix(1, 1);
    C.matrix_type = 0;
    C.matrix[0][0] = 1.01;
    D = s21_sum_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_sub_test) {
    matrix_t A = s21_create_matrix(2, 4), B = s21_create_matrix(2, 4), C = s21_create_matrix(2, 4);
    A.matrix[0][0] = 2; A.matrix[0][1] = 3; A.matrix[0][2] = 5; A.matrix[0][3] = 7;
    A.matrix[1][0] = 2; A.matrix[1][1] = 3; A.matrix[1][2] = 5; A.matrix[1][3] = 7;
    A.matrix_type = 0;
    B.matrix[0][0] = 1; B.matrix[0][1] = 2; B.matrix[0][2] = 3; B.matrix[0][3] = 4;
    B.matrix[1][0] = 1; B.matrix[1][1] = 2; B.matrix[1][2] = 3; B.matrix[1][3] = 4;
    B.matrix_type = 0;
    C.matrix[0][0] = 1; C.matrix[0][1] = 1; C.matrix[0][2] = 2; C.matrix[0][3] = 3;
    C.matrix[1][0] = 1; C.matrix[1][1] = 1; C.matrix[1][2] = 2; C.matrix[1][3] = 3;
    C.matrix_type = 0;
    matrix_t D = s21_sub_matrix(&A, &B);
    int answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(1, 1);
    A.matrix_type = 0;
    A.matrix[0][0] = 1;
    B = s21_create_matrix(1, 2);
    B.matrix_type = 0;
    B.matrix[0][0] = 0.01; B.matrix[0][1] = 3;
    C = s21_create_matrix(1, 1);
    C.matrix_type = 0;
    C.matrix[0][0] = 1.01;
    D = s21_sub_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(1, 1);
    A.matrix_type = 1;
    A.matrix[0][0] = 1;
    B = s21_create_matrix(1, 1);
    B.matrix_type = 0;
    B.matrix[0][0] = 0.01;
    C = s21_create_matrix(1, 1);
    C.matrix_type = 0;
    C.matrix[0][0] = 1.01;
    D = s21_sub_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_mult_test) {
    matrix_t A = s21_create_matrix(3, 3), B = s21_create_matrix(3, 2), C = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = -5; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    B.matrix[0][0] = 8; B.matrix[0][1] = 1;
    B.matrix[1][0] = 7; B.matrix[1][1] = 2;
    B.matrix[2][0] = 2; B.matrix[2][1] = -3;
    B.matrix_type = 0;
    C.matrix[0][0] = 21; C.matrix[0][1] = -5;
    C.matrix[1][0] = 46; C.matrix[1][1] = 8;
    C.matrix[2][0] = 4; C.matrix[2][1] = 4;
    C.matrix_type = 0;
    matrix_t D = s21_mult_matrix(&A, &B);
    int answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(3, 3), B = s21_create_matrix(3, 2), C = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    B.matrix[0][0] = 8; B.matrix[0][1] = 1;
    B.matrix[1][0] = 7; B.matrix[1][1] = 2;
    B.matrix[2][0] = 2; B.matrix[2][1] = -3;
    B.matrix_type = 0;
    C.matrix[0][0] = 21; C.matrix[0][1] = -5;
    C.matrix[1][0] = 46; C.matrix[1][1] = 8;
    C.matrix[2][0] = 4; C.matrix[2][1] = 4;
    C.matrix_type = 0;
    D = s21_mult_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3), B = s21_create_matrix(2, 2), C = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    B.matrix[0][0] = 8; B.matrix[0][1] = 1;
    B.matrix[1][0] = 7; B.matrix[1][1] = 2;
    B.matrix_type = 0;
    C.matrix[0][0] = 21; C.matrix[0][1] = -5;
    C.matrix[1][0] = 46; C.matrix[1][1] = 8;
    C.matrix[2][0] = 4; C.matrix[2][1] = 4;
    C.matrix_type = 0;
    D = s21_mult_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3), B = s21_create_matrix(2, 2), C = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    B.matrix[0][0] = 8; B.matrix[0][1] = 1;
    B.matrix[1][0] = 7; B.matrix[1][1] = 2;
    B.matrix_type = 0;
    C.matrix[0][0] = 21; C.matrix[0][1] = -5;
    C.matrix[1][0] = 46; C.matrix[1][1] = 8;
    C.matrix[2][0] = 4; C.matrix[2][1] = 4;
    C.matrix_type = 0;
    D = s21_mult_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);
    A = s21_create_matrix(2, 3), B = s21_create_matrix(3, 2), C = s21_create_matrix(2, 2);
    A.matrix[0][0] = 1.2; A.matrix[0][1] = -2.4; A.matrix[0][2] = 3.6;
    A.matrix[1][0] = 0.1; A.matrix[1][1] = 0.2; A.matrix[1][2] = 0.3;
    A.matrix_type = 0;
    B.matrix[0][0] = 21; B.matrix[0][1] = 22;
    B.matrix[1][0] = 0.1; B.matrix[1][1] = 0.2;
    B.matrix[2][0] = 6.1; B.matrix[2][1] = 2;
    B.matrix_type = 0;
    C.matrix[0][0] = +1173.0 / 25.0; C.matrix[0][1] = 828.0 / 25.0;
    C.matrix[1][0] = 79.0 / 20.0; C.matrix[1][1] = 71.0 / 25.0;
    C.matrix_type = 0;
    D = s21_mult_matrix(&A, &B);
    answer = s21_eq_matrix(&C, &D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 1);
}
END_TEST


START_TEST(s21_matrix_determinant_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = -5; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    double det = s21_determinant(&A);
    s21_remove_matrix(&A);
    ck_assert_double_eq(det, 78);

    A = s21_create_matrix(0, 0);
    det = s21_determinant(&A);
    s21_remove_matrix(&A);
    ck_assert_double_ne(det, NAN);

    matrix_t B = s21_create_matrix(1, 1);
    B.matrix[0][0] = 3;
    B.matrix_type = 0;
    double det_2 = s21_determinant(&B);
    s21_remove_matrix(&B);
    ck_assert_double_eq(det_2, 3);

    B = s21_create_matrix(1, 1);
    B.matrix[0][0] = 1;
    B.matrix_type = 2;
    det_2 = s21_determinant(&B);
    s21_remove_matrix(&B);
    ck_assert_double_eq(det_2, 1);

    B = s21_create_matrix(1, 1);
    B.matrix[0][0] = 0;
    B.matrix_type = 3;
    det_2 = s21_determinant(&B);
    s21_remove_matrix(&B);
    ck_assert_double_eq(det_2, 0);


    A = s21_create_matrix(1, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = 2;
    A.matrix_type = 0;
    det = s21_determinant(&A);
    s21_remove_matrix(&A);
    ck_assert_double_ne(det, NAN);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    det = s21_determinant(&A);
    s21_remove_matrix(&A);
    ck_assert_double_ne(det, NAN);

    A = s21_create_matrix(2, 3);
    A.matrix[0][0] =  5.0 / 4.0; A.matrix[0][1] = 600.0; A.matrix[0][2] = -10000.0;
    A.matrix[1][0] = -31.0 / 25.0; A.matrix[1][1] = -400.0; A.matrix[1][2] = -50000.0;
    printf("We have matrix:\n");
    det = s21_determinant(&A);
    ck_assert_double_ne(det, NAN);
}

END_TEST

START_TEST(s21_matrix_inverse_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = -5; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    matrix_t B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0/39.0; B.matrix[0][1] = 1.0/6.0; B.matrix[0][2] = -2.0/39.0;
    B.matrix[1][0] = -2.0/39.0; B.matrix[1][1] = 1.0/6.0; B.matrix[1][2] = 4.0/39.0;
    B.matrix[2][0] = 17.0/39.0; B.matrix[2][1] = -1.0/6.0; B.matrix[2][2] = 5.0/39.0;
    B.matrix_type = 0;
    matrix_t C = s21_inverse_matrix(&A);
    int answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = 1.0 / 0.0; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0/39.0; B.matrix[0][1] = 1.0/6.0; B.matrix[0][2] = -2.0/39.0;
    B.matrix[1][0] = -2.0/39.0; B.matrix[1][1] = 1.0/6.0; B.matrix[1][2] = 4.0/39.0;
    B.matrix[2][0] = 17.0/39.0; B.matrix[2][1] = -1.0/6.0; B.matrix[2][2] = 5.0/39.0;
    B.matrix_type = 0;
    C = s21_inverse_matrix(&A);
    answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2;
    A.matrix[2][0] = 1.0; A.matrix[2][1] = 6;
    A.matrix_type = 0;
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0/39.0; B.matrix[0][1] = 1.0/6.0; B.matrix[0][2] = -2.0/39.0;
    B.matrix[1][0] = -2.0/39.0; B.matrix[1][1] = 1.0/6.0; B.matrix[1][2] = 4.0/39.0;
    B.matrix[2][0] = 17.0/39.0; B.matrix[2][1] = -1.0/6.0; B.matrix[2][2] = 5.0/39.0;
    B.matrix_type = 0;
    C = s21_inverse_matrix(&A);
    answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 0.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 0.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 0.0;
    A.matrix_type = 0;
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0/39.0; B.matrix[0][1] = 1.0/6.0; B.matrix[0][2] = -2.0/39.0;
    B.matrix[1][0] = -2.0/39.0; B.matrix[1][1] = 1.0/6.0; B.matrix[1][2] = 4.0/39.0;
    B.matrix[2][0] = 17.0/39.0; B.matrix[2][1] = -1.0/6.0; B.matrix[2][2] = 5.0/39.0;
    B.matrix_type = 0;
    C = s21_inverse_matrix(&A);
    answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_create_test) {
    matrix_t A = s21_create_matrix(3, 3);
    int matrix_type = A.matrix_type;
    s21_remove_matrix(&A);
    ck_assert_int_eq(matrix_type, 3);
    matrix_t B = s21_create_matrix(1, 1);
    matrix_type = B.matrix_type;
    s21_remove_matrix(&B);
    ck_assert_int_eq(matrix_type, 3);
    matrix_t C = s21_create_matrix(0, 0);
    matrix_type = C.matrix_type;
    s21_remove_matrix(&C);
    ck_assert_int_eq(matrix_type, 1);
}
END_TEST

START_TEST(s21_matrix_mult_number_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = -5; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    matrix_t B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 7.5; B.matrix[0][1] = -2.5; B.matrix[0][2] = 5.0;
    B.matrix[1][0] = 10.0; B.matrix[1][1] = 5.0; B.matrix[1][2] = 0;
    B.matrix[2][0] = -12.5; B.matrix[2][1] = 15.0; B.matrix[2][2] = 2.5;
    B.matrix_type = 0;
    double number = 2.5;
    matrix_t C = s21_mult_number(&A, number);
    int answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 2.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 2.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 2.0;
    A.matrix_type = 0;
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0; B.matrix[0][1] = 0.0; B.matrix[0][2] = 0.0;
    B.matrix[1][0] = 0.0; B.matrix[1][1] = 1.0; B.matrix[1][2] = 0.0;
    B.matrix[2][0] = 0.0; B.matrix[2][1] = 0.0; B.matrix[2][2] = 1.0;
    B.matrix_type = 2;
    number = 1.0/2.0;
    C = s21_mult_number(&A, number);
    answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 2.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 2.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 2.0;
    A.matrix_type = 0;
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 0.0; B.matrix[0][1] = 0.0; B.matrix[0][2] = 0.0;
    B.matrix[1][0] = 0.0; B.matrix[1][1] = 0.0; B.matrix[1][2] = 0.0;
    B.matrix[2][0] = 0.0; B.matrix[2][1] = 0.0; B.matrix[2][2] = 0.0;
    B.matrix_type = 3;
    number = 0.0;
    C = s21_mult_number(&A, number);
    answer = s21_eq_matrix(&C, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 1);

    A = s21_create_matrix(1, 1);
    A.matrix_type = 1;
    A.matrix[0][0] = 1;
    B = s21_create_matrix(1, 2);
    B.matrix_type = 0;
    B.matrix[0][0] = 0.01; B.matrix[0][1] = 3;
    matrix_t D = s21_mult_number(&A, number);
    answer = s21_eq_matrix(&D, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&D);
    ck_assert_int_eq(answer, 0);
}
END_TEST


START_TEST(s21_matrix_print_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;
    A.matrix_type = 2;
    s21_print_matrix(&A);
    matrix_t B = s21_create_matrix(3, 3);
    B.matrix_type = 3;
    s21_print_matrix(&B);
    double number = 2.5;
    matrix_t C = s21_mult_number(&A, number);
    int answer = s21_eq_matrix(&C, &B);
    matrix_t *D = NULL;
    s21_print_matrix(D);
    s21_remove_matrix(&A); s21_remove_matrix(&B); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_equal_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;
    A.matrix_type = 2;
    s21_print_matrix(&A);
    matrix_t B = s21_create_matrix(3, 2);
    B.matrix[0][0] = 7.5; B.matrix[0][1] = -2.5;
    B.matrix[1][0] = 10.0; B.matrix[1][1] = 5.0;
    B.matrix[2][0] = -12.5; B.matrix[2][1] = 15.0;
    B.matrix_type = 0;
    int answer = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;
    A.matrix_type = 1;
    s21_print_matrix(&A);
    B = s21_create_matrix(3, 2);
    B.matrix[0][0] = 7.5; B.matrix[0][1] = -2.5;
    B.matrix[1][0] = 10.0; B.matrix[1][1] = 5.0;
    B.matrix[2][0] = -12.5; B.matrix[2][1] = 15.0;
    B.matrix_type = 0;
    answer = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;
    A.matrix_type = 0;
    s21_print_matrix(&A);
    B = s21_create_matrix(3, 2);
    B.matrix[0][0] = 7.5; B.matrix[0][1] = -2.5;
    B.matrix[1][0] = 10.0; B.matrix[1][1] = 5.0;
    B.matrix[2][0] = -12.5; B.matrix[2][1] = 15.0;
    B.matrix_type = 0;
    answer = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
    A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
    A.matrix[2][0] = 12.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;
    A.matrix_type = 0;
    s21_print_matrix(&A);
    B = s21_create_matrix(3, 3);
    B.matrix[0][0] = 1.0; B.matrix[0][1] = 0.0; B.matrix[0][2] = 0.0;
    B.matrix[1][0] = 0.0; B.matrix[1][1] = 1.0; B.matrix[1][2] = 0.0;
    B.matrix[2][0] = 12.01; B.matrix[2][1] = 0.0; B.matrix[2][2] = 1.0;
    B.matrix_type = 0;
    answer = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A); s21_remove_matrix(&B);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_transpose_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    matrix_t C = s21_transpose(&A);
    int answer = s21_eq_matrix(&C, &A);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(s21_matrix_calc_complements_test) {
    matrix_t A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = NAN; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    matrix_t C = s21_calc_complements(&A);
    int answer = s21_eq_matrix(&C, &A);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 2);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2;
    A.matrix[2][0] = 0.0; A.matrix[2][1] = 6;
    A.matrix_type = 0;
    C = s21_calc_complements(&A);
    answer = s21_eq_matrix(&C, &A);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = 1.0 / 0.0; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.matrix_type = 0;
    C = s21_calc_complements(&A);
    answer = s21_eq_matrix(&C, &A);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    A = s21_create_matrix(3, 3);
    A.matrix[0][0] = 3; A.matrix[0][1] = -1; A.matrix[0][2] = 2;
    A.matrix[1][0] = 4; A.matrix[1][1] = 2; A.matrix[1][2] = 0;
    A.matrix[2][0] = 2; A.matrix[2][1] = 6; A.matrix[2][2] = 1;
    A.rows = -1;
    A.matrix_type = 0;
    C = s21_calc_complements(&A);
    answer = s21_eq_matrix(&C, &A);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);

    matrix_t *D = NULL;
    C = s21_calc_complements(D);
    answer = s21_eq_matrix(&C, D);
    s21_remove_matrix(&A); s21_remove_matrix(&C);
    ck_assert_int_eq(answer, 0);
}
END_TEST

START_TEST(internal_cube_test) {
    figure_t figure;
    creat_cube(&figure);
    ck_assert_int_eq(18, figure.lines_number);
    remove_figure(&figure);
}
END_TEST

START_TEST(loading_test) {
 const char file_name[20] = "table-1.obj";
    figure_t figure;
    read_data_from_file(file_name, &figure);
    ck_assert_int_eq(7384, figure.lines_number);
    remove_figure(&figure);
}
END_TEST

START_TEST(miss_loading_test) {
 const char file_name[20] = "table-1.obj";
    figure_t figure;
  int answer = read_data_from_file("none.obj", &figure);
    ck_assert_int_eq(1, answer);
}
END_TEST

START_TEST(loading_2_test) {
 const char file_name[20] = "cube-4.obj";
    figure_t figure;
    read_data_from_file(file_name, &figure);
    FILE *obj_file;
    obj_file = fopen(file_name, "r");
    int lines_number = number_of_lines_from_file(obj_file);
    char **strs_from_file;
        strs_from_file = (char**)calloc(lines_number, sizeof(char *));
        for (int i = 0; i < lines_number; i++) {
            strs_from_file[i] = (char *)calloc(255, sizeof(char));
            for (int j = 0; j < 255; j++) strs_from_file[i][j] = '\0';
        }
    print_str_from_file(strs_from_file, lines_number);
    ck_assert_int_eq(17, lines_number);
    remove_figure(&figure);
    for (int i = 0; i < lines_number; i++) free(strs_from_file[i]);
    free(strs_from_file);
}
END_TEST

START_TEST(move_test) {
    figure_t figure;
    creat_cube(&figure);
    move_figure(&figure, 100, 100, 100);
    ck_assert_int_eq(0, (int)figure.dots[0][0]);
    remove_figure(&figure);
}
END_TEST

START_TEST(resize_test) {
    figure_t figure;
    creat_cube(&figure);
    resize_figure(&figure, 2, 2, 2);
    ck_assert_int_eq(-200, (int)figure.dots[0][0]);
    remove_figure(&figure);
}
END_TEST

START_TEST(rotate_test) {
    figure_t figure;
    creat_cube(&figure);
    rotate_figure(&figure, S21_PI, S21_PI, S21_PI);
    ck_assert_int_eq(-99, (int)figure.dots[0][0]);
    remove_figure(&figure);
}
END_TEST

START_TEST(transform_test) {
    figure_t figure;
    creat_cube(&figure);
    transform_figure(&figure, 0, 0, 1);
    print_figure(&figure);
    ck_assert_int_eq(-110, (int)figure.dots[0][0]);
    remove_figure(&figure);
}
END_TEST

START_TEST(multi_move_test) {
    figure_t figure;
    creat_cube(&figure);
    multi_move(&figure, 10,10,10, 2,2,2,S21_PI,0,0,0,0,0);
    print_figure(&figure);
    ck_assert_int_eq(-190, (int)figure.dots[0][0]);
    remove_figure(&figure);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("s21_matrix");
  SRunner *sr = srunner_create(s1);
  int nf;

  TCase *tc1_1 = tcase_create("s21_matrix_sum");
  tcase_add_test(tc1_1, s21_matrix_sum_test);
  suite_add_tcase(s1, tc1_1);

  TCase *tc1_2 = tcase_create("s21_matrix_sub");
  tcase_add_test(tc1_2, s21_matrix_sub_test);
  suite_add_tcase(s1, tc1_2);

  TCase *tc1_3 = tcase_create("s21_matrix_mult");
  tcase_add_test(tc1_3, s21_matrix_mult_test);
  suite_add_tcase(s1, tc1_3);

  TCase *tc1_4 = tcase_create("s21_matrix_determinant");
  tcase_add_test(tc1_4, s21_matrix_determinant_test);
  suite_add_tcase(s1, tc1_4);

  TCase *tc1_5 = tcase_create("s21_matrix_inverse");
  tcase_add_test(tc1_5, s21_matrix_inverse_test);
  suite_add_tcase(s1, tc1_5);

  TCase *tc1_6 = tcase_create("s21_matrix_create");
  tcase_add_test(tc1_6, s21_matrix_create_test);
  suite_add_tcase(s1, tc1_6);

  TCase *tc1_7 = tcase_create("s21_matrix_mult_number");
  tcase_add_test(tc1_7, s21_matrix_mult_number_test);
  suite_add_tcase(s1, tc1_7);

  TCase *tc1_8 = tcase_create("s21_matrix_print_number");
  tcase_add_test(tc1_8, s21_matrix_print_test);
  suite_add_tcase(s1, tc1_8);

  TCase *tc1_9 = tcase_create("s21_matrix_equal_number");
  tcase_add_test(tc1_9, s21_matrix_equal_test);
  suite_add_tcase(s1, tc1_9);

  TCase *tc1_10 = tcase_create("s21_matrix_transpose_number");
  tcase_add_test(tc1_10, s21_matrix_transpose_test);
  suite_add_tcase(s1, tc1_10);

  TCase *tc1_11 = tcase_create("s21_matrix_calc_complements_number");
  tcase_add_test(tc1_11, s21_matrix_calc_complements_test);
  suite_add_tcase(s1, tc1_11);

  TCase *tc1_12 = tcase_create("internal_cube");
  tcase_add_test(tc1_12, internal_cube_test);
  suite_add_tcase(s1, tc1_12);

  TCase *tc1_13 = tcase_create("loading");
  tcase_add_test(tc1_13, loading_test);
  suite_add_tcase(s1, tc1_13);

  TCase *tc1_14 = tcase_create("miss_loading");
  tcase_add_test(tc1_14, miss_loading_test);
  suite_add_tcase(s1, tc1_14);

  TCase *tc1_15 = tcase_create("loading_2");
  tcase_add_test(tc1_15, loading_2_test);
  suite_add_tcase(s1, tc1_15);

  TCase *tc1_16 = tcase_create("move");
  tcase_add_test(tc1_16, move_test);
  suite_add_tcase(s1, tc1_16);

  TCase *tc1_17 = tcase_create("resize");
  tcase_add_test(tc1_17, resize_test);
  suite_add_tcase(s1, tc1_17);

  TCase *tc1_18 = tcase_create("rotate");
  tcase_add_test(tc1_18, rotate_test);
  suite_add_tcase(s1, tc1_18);

  TCase *tc1_19 = tcase_create("transform");
  tcase_add_test(tc1_19, transform_test);
  suite_add_tcase(s1, tc1_19);

  TCase *tc1_20 = tcase_create("multi-move");
  tcase_add_test(tc1_20, multi_move_test);
  suite_add_tcase(s1, tc1_20);

  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
