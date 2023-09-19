#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t answer;
    if (rows <= 0 || columns <= 0) {
        answer.matrix_type = INCORRECT_MATRIX;
        answer.rows = rows;
        answer.columns = columns;
        answer.matrix = NULL;
    } else {
        answer.matrix_type = ZERO_MATRIX;
        answer.rows = rows;
        answer.columns = columns;
        answer.matrix = (double **)calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++) {
            answer.matrix[i] = (double *)calloc(columns, sizeof(double));
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                answer.matrix[i][j] = 0;
            }
        }
    }
    return answer;
}

void s21_remove_matrix(matrix_t *A) {
    if (A != NULL && A->matrix_type != INCORRECT_MATRIX) {
        if (A->rows > 0) {
            for (int i = 0; i < A->rows; i++) {
                free(A->matrix[i]);
            }
            free(A->matrix);
        }
        A->matrix_type = INCORRECT_MATRIX;
    }
}

int check_for_dimention_and_type(matrix_t *A, matrix_t *B) {
    int answer = 1;
    if (A->matrix_type == 1 || B->matrix_type == 1) {
        answer = 0;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        answer = 0;
    }
    return answer;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int answer = 1;
    if (s21_check_matrix_for_no_mistakes(A) == 0 || s21_check_matrix_for_no_mistakes(B) == 0) {
        answer = 0;
    } else if (check_for_dimention_and_type(A, B)) {
        int flag = 0;
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                double diff = fabs(A->matrix[i][j] - B->matrix[i][j]);
                if (diff > +1e-07) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1) answer = 0;
    } else {
        answer = 0;
    }
    return answer;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    matrix_t rezult;
    if (!s21_check_matrix_for_no_mistakes(A) || !s21_check_matrix_for_no_mistakes(B)) {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    } else if (check_for_dimention_and_type(A, B)) {
        rezult = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                rezult.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
    } else {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t rezult;
    if (!s21_check_matrix_for_no_mistakes(A) || !s21_check_matrix_for_no_mistakes(B)) {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    } else if (check_for_dimention_and_type(A, B)) {
        rezult = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                rezult.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
    } else {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t rezult;
    if (s21_check_matrix_for_no_mistakes(A)) {
        rezult = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                rezult.matrix[i][j] = A->matrix[i][j] * number;
            }
        }
        s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
    } else {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t rezult;
    int flag = 1;
    if (s21_check_matrix_for_no_mistakes(A) && s21_check_matrix_for_no_mistakes(B)) {
        if (A->columns == B->rows) {
            rezult = s21_create_matrix(A->rows, B->columns);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                    double temp_number = 0;
                    for (int k = 0; k < B->rows; k++) {
                        temp_number += A->matrix[i][k] * B->matrix[k][j];
                    }
                    rezult.matrix[i][j] = temp_number;
                }
            }
            s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag == 0) {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

matrix_t s21_transpose(matrix_t *A) {
    matrix_t rezult;
    if (!s21_check_matrix_for_no_mistakes(A)) {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    } else {
        rezult = s21_create_matrix(A->columns, A->rows);
        for (int i = 0; i < A->columns; i++) {
            for (int j = 0; j < A->rows; j++) {
                rezult.matrix[i][j] = A->matrix[j][i];
            }
        }
        s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
    }
    return rezult;
}

matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t rezult;
    if (s21_check_matrix_for_no_mistakes(A)) {
        if (A->rows == A->columns) {
            rezult = s21_create_matrix(A->rows, A->columns);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    int det = A->rows - 1, counter_rows = 0, counter_columns;
                    matrix_t temp = s21_create_matrix(det, det);
                    for (int k = 0; k < A->rows; k++) {
                        if (k != i) {
                            counter_columns = 0;
                            for (int m = 0; m < A->columns; m++) {
                                if (m != j) {
                                    temp.matrix[counter_rows][counter_columns] = A->matrix[k][m];
                                    counter_columns++;
                                }
                            }
                            counter_rows++;
                        }
                    }
                    temp.matrix_type = 0;
                    rezult.matrix[i][j] = s21_determinant(&temp) * ((i + j)%2 == 0 ? 1: -1);
                    s21_remove_matrix(&temp);
                }
            }
            s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
        } else {
            rezult = s21_create_matrix(1, 1);
            rezult.matrix_type = 1;
        }
    } else {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

double s21_determinant(matrix_t *A) {
    double answer;
    if (!s21_check_matrix_for_no_mistakes(A)) {
        answer = NAN;
    } else if (A->columns != A->rows) {
        answer = NAN;
    } else if (A->matrix_type == ZERO_MATRIX) {
        answer = 0;
    } else if (A->matrix_type == 2) {
        answer = 1;
    } else {
        if (A->rows == 1) {
            answer = A->matrix[0][0];
        } else if (A->rows == 2) {
            answer = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else {
            answer = 0;
            for (int i = 0; i < A->rows; i++) {
                int dem = A->rows - 1;
                matrix_t temp = s21_create_matrix(dem, dem);
                int counter_columns = 0;
                for (int j = 0; j < A->rows; j++) {
                    if (j != i) {
                        for (int k = 1; k < A->rows; k++) {
                            temp.matrix[k - 1][counter_columns] = A->matrix[k][j];
                        }
                        counter_columns++;
                    }
                }
                temp.matrix_type = 0;
                answer += A->matrix[0][i] * s21_determinant(&temp) * ((i % 2) == 0 ? 1 : -1);
                s21_remove_matrix(&temp);
            }
        }
    }
    return answer;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
        matrix_t rezult;
        int flag = 1;
    if (s21_check_matrix_for_no_mistakes(A)) {
        if (A->rows == A->columns) {
            double det = s21_determinant(A);
            if (det != 0.0) {
                matrix_t temp_rezult = s21_calc_complements(A);
                rezult  = s21_transpose(&temp_rezult);
                for (int i = 0; i < A->rows; i++) {
                    for (int j = 0; j < A->columns; j++) {
                        rezult.matrix[i][j] /= det;
                    }
                }
                s21_matrix_type_check_for_correct_zero_and_identity(&rezult);
                s21_remove_matrix(&temp_rezult);
            } else {
                flag = 0;
            }
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }
    if (flag == 0) {
        rezult = s21_create_matrix(1, 1);
        rezult.matrix_type = 1;
    }
    return rezult;
}

int s21_check_matrix_for_no_mistakes(matrix_t *A) {
    int rezult = 1;
    if (A == NULL) {
        rezult = 0;
    } else if (A->matrix_type == 1) {
        rezult = 0;
    } else if (A->rows <= 0 || A->columns <= 0) {
        rezult = 0;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (isinf(A->matrix[i][j])) {
                    rezult = 0;
                    break;
                }
                if (isnan(A->matrix[i][j])) {
                    rezult = 0;
                    break;
                }
            }
            if (rezult == 0) break;
        }
    }
    return rezult;
}

void s21_matrix_type_check_for_correct_zero_and_identity(matrix_t *A) {
    if (A != NULL) {
        if (A->rows > 0 && A->columns > 0) {
            int zero_count = 0;
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    if (fabs(A->matrix[i][j]) < +1e-07) {
                        zero_count++;
                    }
                }
            }
            if (zero_count == A->rows * A->columns) {
                A->matrix_type = 3;
            } else {
                zero_count = 0;
                if (A->rows == A->columns) {
                    int one_count = 0;
                    for (int i = 0; i < A->rows; i++) {
                        for (int j = 0; j < A->columns; j++) {
                            if (i == j && fabs((A->matrix[i][j]) - 1.0) < +1e-07) {
                                one_count++;
                            } else if (fabs(A->matrix[i][j]) < +1e-07) {
                                zero_count++;
                            }
                        }
                    }
                    if (zero_count == A->rows * A->columns - A->rows && one_count == A->rows) {
                        A->matrix_type = 2;
                    } else {
                        A->matrix_type = 0;
                    }
                } else {
                    A->matrix_type = 0;
                }
            }
        } else {
            A->matrix_type = 1;
        }
    }
}


void s21_print_matrix(matrix_t *A) {
    if (A == NULL) {
        printf("There is no matrix. NULL pointer is given\n");
    } else if (A->matrix_type == INCORRECT_MATRIX) {
        printf("This is INCORRECT_MATRIX!!!\n");
    } else if (A->matrix_type == IDENTITY_MATRIX) {
        printf("This matrix is an IDENTITY_MATRIX!!!\n");
        printf("A->rows = %d A->columns = %d\n", A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                printf("%+7.1f   ", A->matrix[i][j]);
            }
            printf("\n");
        }
    } else if (A->matrix_type == ZERO_MATRIX) {
        printf("This matrix is ZERO_MATRIX!!!\n");
        printf("A->rows = %d A->columns = %d\n", A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                printf("%+7.1f   ", A->matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("This matrix is a CORRECT_MATRIX!!!\n");
        printf("A->rows = %d A->columns = %d\n", A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                printf("%+7.1f   ", A->matrix[i][j]);
            }
            printf("\n");
        }
    }
}
