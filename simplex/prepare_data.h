#include <stdio.h>
#include "gsl/vector/gsl_vector.h"
#include "gsl/matrix/gsl_matrix.h"

gsl_matrix * fscan_mat(const char* filename);
gsl_vector * fscan_vec(const char* filename);