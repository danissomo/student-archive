#include "prepare_data.h"
//matrix[y,x]; y- по вертикали, x - по горизонтали
int main(){
  gsl_matrix * Mat       = fscan_mat("matrix.txt");
  gsl_vector * VecB      = fscan_vec("vectorB.txt"),
             * last_row  = gsl_vector_alloc(Mat->size2),
             * drive_col = gsl_vector_alloc(Mat->size1),
             * drive_row = gsl_vector_alloc(Mat->size2),
             * drive_row_buf = gsl_vector_alloc(Mat->size2),
             * buf_row   = gsl_vector_alloc(Mat->size2),
             * VecB_buf  = gsl_vector_alloc(VecB->size);
  
  gsl_vector_memcpy(VecB_buf, VecB);
int end_simplex = 0;
for(int i = 0; !end_simplex ; i++){
  gsl_matrix_get_row(last_row, Mat, 0);
  int mi_lr = gsl_vector_min_index(last_row);
  gsl_matrix_get_col(drive_col, Mat, mi_lr);
  gsl_vector_div(VecB_buf, drive_col);

  int min = -1, min_indx;
  for(int i = 0; i < VecB_buf->size; i++  ){
    double cur = gsl_vector_get(VecB_buf, i);
    if( cur > 0 && (cur < min || min == -1) ){
      min_indx = i;
      min = cur;
    }
  }

  gsl_matrix_get_row(drive_row, Mat, min_indx);
  gsl_vector_scale(drive_row, 1/gsl_vector_get(drive_row,mi_lr));
  gsl_vector_memcpy(drive_row_buf, drive_row);
  gsl_matrix_set_row(Mat, min_indx, drive_row );
  for (int i = 0; i < Mat->size1; i++){
    if(i == min_indx) continue;
    gsl_matrix_get_row(buf_row, Mat, i);
    gsl_vector_memcpy(drive_row_buf, drive_row);
    gsl_vector_scale(drive_row_buf, gsl_vector_get(buf_row, mi_lr));
    gsl_vector_sub(buf_row, drive_row_buf);
    gsl_matrix_set_row(Mat,i,buf_row);
  }
  for (int i = 0; i < Mat->size1; i++, printf("\n"))
    for (int j = 0; j < Mat->size2; j++)
      printf("%7.3g ", gsl_matrix_get(Mat, i, j));
  printf("\n");

  gsl_matrix_get_row(buf_row, Mat, 0);
  end_simplex = 1;
  for(int  i = 1; i < buf_row->size-1; i++)
    if(gsl_vector_get(buf_row, i) < 0){
      end_simplex = 0;
      break;
    }
  
}
  
  return 0;
}