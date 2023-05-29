#include "prepare_data.h"

gsl_matrix * fscan_mat(const char filename[]){
	FILE *matFile = fopen(filename, "r");
	if(matFile == NULL) {
		fprintf(stderr, "Errno %d\n", errno);
		return NULL;
	}
	int width, height;
   	fscanf(matFile,"%d %d", &width, &height);
	gsl_matrix * Mat = gsl_matrix_alloc(height, width);
	gsl_matrix_fscanf(matFile, Mat);
	fclose(matFile);
	return Mat;

}


gsl_vector * fscan_vec(const char filename[]){
	FILE *vecFile = fopen(filename, "r");
	if(vecFile == NULL) {
		fprintf(stderr, "Errno %d\n", errno);
		return NULL;
	}
	int  height;
   	fscanf(vecFile,"%d", &height);
	gsl_vector * vec = gsl_vector_alloc(height);
	gsl_vector_fscanf(vecFile, vec);
	fclose(vecFile);
	return vec;

}
