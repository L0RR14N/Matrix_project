#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef double MATRIX_TYPE;

typedef struct {
	int rows;
	int cols;
	MATRIX_TYPE** data;
} matrix;

typedef matrix submatrix;

matrix* create_matrix(int rows, int cols);
void free_matrix(matrix* matrix);

matrix* load_matrix_from_file(const char* filename);
int save_matrix_to_file(const matrix* matrix, const char* filename);

matrix* add_matrices(const matrix* A, const matrix* B);
matrix* subtract_matrices(const matrix* A, const matrix* B);
matrix* multiply_matrices(const matrix* A, const matrix* B);
matrix* transpose_matrix(const matrix* matrix);
MATRIX_TYPE determinant(const matrix* matrix);

matrix* copy_matrix(const matrix* source);
int are_matrices_equal(const matrix* A, const matrix* B);

#endif
