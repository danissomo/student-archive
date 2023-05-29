#include <stdio.h>
#include <malloc.h>
#include "dfp.h"
#include "matrix_tricks.h"
double func(double **);
int main(){
	int dimentions = 3;
	double **H_0 = malloc(sizeof(double *) * dimentions);
	double **x_vec_0 = malloc(sizeof(double)* dimentions);
	double **r;
	
	for (int i = 0; i < dimentions; i++){
		H_0[i] = malloc(sizeof(double) * dimentions);
		x_vec_0[i] = malloc(sizeof(double));
		for (int j = 0; j < dimentions; j++)
			if (i == j) H_0[i][j] = 1;
			else H_0[i][j] = 0;
	}
	x_vec_0[0][0] = 7;
	x_vec_0[1][0] = 0; 
	x_vec_0[2][0] = 2; 
	
	r = dfp(func, x_vec_0, H_0, dimentions, 0.001);
	printf("\n min x vec\n");
	for(int  i = 0; i < dimentions; i++)
		printf("%f ", r[i][0]);
	printf("\n");
}
double func(double **x_vec){
	return x_vec[0][0]*x_vec[0][0] + x_vec[1][0]*x_vec[1][0]+x_vec[2][0]*x_vec[2][0] - x_vec[0][0]*x_vec[1][0] - x_vec[0][0]*x_vec[2][0] ;
}
