#include "../include/matrix/matrix.h"
#include "../include/output/output.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

matrix* create_matrix(int rows, int cols) {
    matrix* new_matrix = (matrix*)malloc(sizeof(matrix));
    if (!new_matrix) return NULL;

    new_matrix->rows = rows;
    new_matrix->cols = cols;

    new_matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));
    if (!new_matrix->data) {
        free(new_matrix);
        return NULL;
    }

    for (int current_row = 0; current_row < rows; current_row++) {
        new_matrix->data[current_row] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE));

		if (!new_matrix->data[current_row]) {
            for (int cleanup_row = 0; cleanup_row < current_row; cleanup_row++) {
				free(new_matrix->data[cleanup_row]);
			}
            free(new_matrix->data);
            free(new_matrix);
            return NULL;
        }
    }
    return new_matrix;
}

void free_matrix(matrix* matrix_to_free) {
    if (!matrix_to_free) return;

    for (int row = 0; row < matrix_to_free->rows; row++) {
        free(matrix_to_free->data[row]);
    }
    free(matrix_to_free->data);
    free(matrix_to_free);
}

matrix* multiply_matrices(const matrix* A, const matrix* B) {
    if (!A || !B || A->cols != B->rows) return NULL;

    matrix* result = create_matrix(A->rows, B->cols);
    if (!result) return NULL;

    for(int res_row = 0; res_row < A->rows; res_row++) {
        for (int res_col = 0; res_col < B->cols; res_col++) {
            result->data[res_row][res_col] = 0;
            for (int element_idx = 0; element_idx < A->cols; element_idx++) {
                result->data[res_row][res_col] +=
					 A->data[res_row][element_idx] *
					 B->data[element_idx][res_col];
            }
        }
    }
    return result;
}

matrix* add_matrices(const matrix* A, const matrix* B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;

    matrix* sum_matrix = create_matrix(A->rows, A->cols);
    if (!sum_matrix) return NULL;

    for (int row = 0; row < A->rows; row++) {
        for (int col = 0; col < A->cols; col++) {
            sum_matrix->data[row][col] = A->data[row][col] + B->data[row][col];
        }
    }
    return sum_matrix;
}

matrix* subtract_matrices(const matrix* A, const matrix* B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;

    matrix* difference = create_matrix(A->rows, A->cols);
    if (!difference) return NULL;

    for(int row = 0; row < A->rows; row++) {
        for(int col = 0; col < A->cols; col++) {
            difference->data[row][col] = A->data[row][col] - B->data[row][col];
        }
    }
    return difference;
}

matrix* transpose_matrix(const matrix* original) {
    if (!original) return NULL;

    matrix* transposed = create_matrix(original->cols, original->rows);
    if (!transposed) return NULL;

    for(int src_row = 0; src_row < original->rows; src_row++) {
        for(int src_col = 0; src_col < original->cols; src_col++) {
            transposed->data[src_col][src_row] =
				original->data[src_row][src_col];
        }
    }
    return transposed;
}

matrix* load_matrix_from_file(const char* filename) {
    if (!filename) return NULL;

    FILE* input_file = fopen(filename, "r");
    if (!input_file) return NULL;

    int rows, cols;
    if (fscanf(input_file, "%d %d", &rows, &cols) != 2) {
        fclose(input_file);
        return NULL;
    }

    matrix* loaded_matrix = create_matrix(rows, cols);
    if (!loaded_matrix) {
        fclose(input_file);
        return NULL;
    }

    for(int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (fscanf(input_file, "%lf",
					 &loaded_matrix->data[row][col]) != 1) {
                fclose(input_file);
                free_matrix(loaded_matrix);
                return NULL;
            }
        }
    }

    fclose(input_file);
    return loaded_matrix;
}

int save_matrix_to_file(const matrix* matrix_to_save, const char* filename) {
    if (!matrix_to_save || !filename) return -1;

    FILE* output_file = fopen(filename, "w");
    if (!output_file) return -1;

    fprintf(output_file, "%d %d\n", matrix_to_save->rows, matrix_to_save->cols);
    for (int row = 0; row < matrix_to_save->rows; row++) {
        for (int col = 0; col < matrix_to_save->cols; col++) {
            fprintf(output_file, "%f ", matrix_to_save->data[row][col]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
    return 0;
}

matrix* copy_matrix(const matrix* source_matrix) {
    if (!source_matrix) return NULL;

    matrix* matrix_copy = create_matrix(source_matrix->rows, 
		source_matrix->cols);
    if (!matrix_copy) return NULL;

    for (int row = 0; row < source_matrix->rows; row++) {
        for (int col = 0; col < source_matrix->cols; col++) {
            matrix_copy->data[row][col] = source_matrix->data[row][col];
        }
    }

    return matrix_copy;
}

int are_matrices_equal(const matrix* A, const matrix* B) {
    if (!A || !B) return 0;
    if (A->rows != B->rows || A->cols != B->cols) return 0;

	const double tolerance = 1e-9;
    for (int row = 0; row < A->rows; row++) {
        for(int col = 0; col < A->cols; col++) {
            if (fabs(A->data[row][col] - B->data[row][col]) > tolerance) {
                return 0;
            }
        }
    }

    return 1;
}

MATRIX_TYPE determinant(const matrix* input_matrix) {
    if (!input_matrix || input_matrix->rows != input_matrix->cols) return 0;

    int matrix_size = input_matrix->rows;
    if (matrix_size == 1) return input_matrix->data[0][0];

    MATRIX_TYPE det = 0;
    matrix* minor_matrix = create_matrix(matrix_size-1, matrix_size-1);
    if (!minor_matrix) return 0;

    for (int pivot_col = 0; pivot_col < matrix_size; pivot_col++) {
        int minor_row = 0;
        for (int src_row = 1; src_row < matrix_size; src_row++) {
            int minor_col = 0;
            for (int src_col = 0; src_col < matrix_size; src_col++) {
                if (src_col == pivot_col) continue;
                minor_matrix->data[minor_row][minor_col] = input_matrix->data[src_row][src_col];
                minor_col++;
            }
            minor_row++;
        }
		MATRIX_TYPE sign = (pivot_col % 2 == 0) ? 1 : -1;
        det += sign * input_matrix->data[0][pivot_col] * determinant(minor_matrix);
    }

    free_matrix(minor_matrix);
    return det;
}
