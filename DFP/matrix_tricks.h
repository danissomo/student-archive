#include <stdlib.h>
#include <malloc.h>
#ifndef MATRIX_TRICKS
#define MATRIX_TRICKS
double ** _matrix_multiply(double  **matrix_1, double** matrix_2, int len_1_hor, int len_1_vert, int len_2_hor, int len_2_vert);
double ** _matrix_sum(double  **matrix_1, double** matrix_2, int len_hor, int len_vert);
double ** _matrix_minus(double  **matrix_1, double** matrix_2, int len_hor, int len_vert);
double ** _matrix_mul_num(double **matrix, double scalar,  int len_hor , int len_vert);
double ** _matrix_trans(double ** matrix, int len_hor, int len_vert);
#endif