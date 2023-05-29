#include "dfp.h"
#include "matrix_tricks.h"
void _grad(double (*f)(double**), double	** point, int len, double eps, double** to_write){
	for(int i = 0; i < len; i++){
		point[i][0] += eps;
		double r = f(point);
		point[i][0]-=2*eps;
		double l = f(point);
		point[i][0] += eps;
		to_write[i][0] = (r-l)/(eps);
	}
}
double **dfp(double (*f)(double**), double** x_vec, double **H_matrix, int len, double eps){
	int t =0 ;
	double **grad = (double**)malloc(sizeof(double)*len);
	double **P_vec;
	double **S_vec;
	double **y_vec = (double**)malloc(sizeof(double*)*len);
	double **result = (double**)malloc(sizeof(double*)*len);
	for(int i=0; i < len; i++){
		
		y_vec[i] = (double*)malloc(sizeof(double));
		grad[i] = (double*)malloc(sizeof(double));
		y_vec[i][0] = x_vec[i][0];
		result[i] = (double*)malloc(sizeof(double));
	}
	
	alg_start:
	for(int j = 0; j < len; j++){
		printf("\n ----new step----");
		_grad(f, y_vec, len, eps, grad);
		printf("\ngrad:\n");
		for(int i = 0; i<len; i++){
			for(int j = 0; j < 1;j ++)
				printf("%f ", grad[i][j]);
			printf("\n");
		}
		double **buff=  _matrix_multiply(H_matrix, grad, len, len, 1, len);
		S_vec = _matrix_mul_num(buff,-1,1, len);
		printf("\nS_vec:\n");
		for(int i = 0; i<len; i++){
			for(int j = 0; j < 1;j ++)
				printf("%f ", S_vec[i][j]);
			printf("\n");
		}
		free(buff);
		double left = -100, right = 100;
		while(fabs(left-right)/2 > eps){
			double  mid = (right+left)/2;
			double ** buff  = _matrix_mul_num(S_vec, mid+eps, 1, len);
			double **righ_x = _matrix_sum(y_vec, buff, 1, len);
			free(buff);
			buff  = _matrix_mul_num(S_vec, mid-eps, 1, len);
			double **left_x = _matrix_sum(y_vec, buff, 1, len);
			free(buff);

			double left_f = f(left_x), right_f = f(righ_x);
			if(left_f < right_f) right = mid;
			else left = mid;
			free(left_x);
			free(righ_x);
		}
		double lambda = (left+right)/2;
		P_vec  = _matrix_mul_num(S_vec,lambda , 1, len);
		double **y_p_1 = _matrix_sum(y_vec, P_vec, 1, len);
		//вычисление H _+1

		for(int i=0;i  < len; i++ )
			y_vec[i][0]=y_p_1[i][0];
		double **g1=  (double**)malloc(sizeof(double)*len);
		for(int i = 0; i < len; i++)
			g1[i]=  (double*)malloc(sizeof(double));
		
		_grad(f, y_p_1, len, eps, g1);
		double **q = _matrix_minus(g1, grad, 1, len);
		double **qT = _matrix_trans(q, 1, len);
		double ** P_vecT = _matrix_trans(P_vec, 1, len);
		double ** P_PT  = _matrix_multiply(P_vec, P_vecT, 1, len, len, 1);
		double ** PT_q =  _matrix_multiply(P_vecT, q, len, 1, 1, len);
		double **result1 = _matrix_mul_num(P_PT, 1/PT_q[0][0], len, len);

		for(int i =0; i<len; i++)
			y_vec[i][0] = y_p_1[i][0];
		free(P_vec);
		free(y_p_1);
		free( P_vecT);
		free( P_PT  );
		free( PT_q );
		
		double ** H_q = _matrix_multiply(H_matrix, q, len, len, 1, len);
		double **qT_H__q = _matrix_multiply(qT, H_q, len, 1, 1, len );
		
		double ** H_q_qT = _matrix_multiply(H_q, qT, 1, len, len, 1);
		double ** H_q_qT_H  = _matrix_multiply(H_q_qT, H_matrix, len, len, len, len);
		double ** result2 = _matrix_mul_num(H_q_qT_H, 1/qT_H__q[0][0], len, len);
		double ** deltaH = _matrix_minus(result1, result2, len, len);
		double ** H_matrix_buf = _matrix_sum(H_matrix, deltaH, len, len);
		for(int i = 0; i < len; i++)
			for(int j=0; j <len; j++)
				H_matrix[i][j] = H_matrix_buf[i][j];  
		
		printf("\nH_matrix:\n");
		for(int i = 0; i<len; i++){
			for(int j = 0; j < len;j ++)
				printf("%f ", H_matrix[i][j]);
			printf("\n");
		}
		printf("\ny_vec:\n");
		
		//free(g1);
		free(q);
		free(qT);
		free(result1);
		free(result2);
		free(H_q);
		free(H_q_qT);
		free(H_q_qT_H);
		//free(result2 );
		free(deltaH);
		free(H_matrix_buf);
	}

	double grad_len=0;
	_grad(f, result, len, eps, grad);
	for(int i = 0; i < len; i++)
		grad_len+=  grad[i][0]*grad[i][0];
	grad_len= sqrt(grad_len);
	 if(grad_len > eps )
	 	goto alg_start;
	 
	for(int i = 0; i<len; i++){
			for(int j = 0; j < 1;j ++)
				printf("%f ", y_vec[i][j]);
			printf("\n");
		}
	
	free(grad); 
	free(P_vec);
	free(S_vec);
	return y_vec;
}
