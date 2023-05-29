#include "matrix_tricks.h"
double ** _matrix_multiply(double  **matrix_1, double** matrix_2, int len_1_hor, int len_1_vert, int len_2_hor, int len_2_vert){
	if(len_1_hor != len_2_vert || len_1_vert < len_2_hor) return NULL;
	double ** result = (double**)malloc(len_1_vert*sizeof(double*));
	for(int i =0; i < len_1_vert; i++)
		result[i] = (double*)malloc(len_2_hor*sizeof(double));
	for(int i  = 0; i< len_1_vert; i++)
		for(int j = 0; j < len_2_hor; j++){
			double sum = 0;
			for(int k = 0; k < len_1_hor; k++)
				sum+=matrix_1[i][k]*matrix_2[k][j];
				

			result[i][j] = sum; 
		}
	


	return result;
}
double ** _matrix_sum(double  **matrix_1, double** matrix_2, int len_hor, int len_vert){
	double ** result = (double**)malloc(len_vert*sizeof(double*));
	for(int i = 0; i < len_vert; i++){
		result[i] = (double*)malloc(len_hor*sizeof(double));
		for(int j = 0 ; j < len_hor; j++)
			result[i][j]= matrix_1[i][j] + matrix_2[i][j];
	}

	return result;

}
double ** _matrix_minus(double  **matrix_1, double** matrix_2, int len_hor, int len_vert){
	double ** result = (double**)malloc(len_vert*sizeof(double*));
	for(int i = 0; i < len_vert; i++){
		result[i] = (double*)malloc(len_hor*sizeof(double));
		for(int j = 0 ; j < len_hor; j++)
			result[i][j]= matrix_1[i][j] - matrix_2[i][j];
	}

	return result;

}

double ** _matrix_mul_num(double **matrix, double scalar,  int len_hor , int len_vert){
	double ** result = (double**)malloc(len_vert*sizeof(double*));
	for(int i = 0; i < len_vert; i++){
		result[i] = (double*)malloc(len_hor*sizeof(double));
		for(int j = 0 ; j < len_hor; j++)
			result[i][j]= matrix[i][j]*scalar;
	}

	return result;

}

double ** _matrix_trans(double ** matrix, int len_hor, int len_vert){
	double ** result = (double**)malloc(len_hor*sizeof(double*));
	for(int i = 0; i < len_vert; i++){
		result[i] = (double*)malloc(len_vert*sizeof(double));
		for(int j = 0 ; j < len_hor; j++)
			result[j][i]= matrix[i][j];
	}
	return result;
}