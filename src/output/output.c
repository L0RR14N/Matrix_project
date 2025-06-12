#include "../include/matrix/matrix.h"
#include "../include/output/output.h"
#include <stdio.h>

void print_matrix(const matrix* matrix_to_print) {
	if (!matrix_to_print) {
		printf("NULL matrix\n");
		return;
	}

	for (int current_row = 0; current_row < matrix_to_print->rows; current_row++) {
		for (int current_col = 0; current_col < matrix_to_print->cols; current_col++) {
			printf("%8.2f ", matrix_to_print->data[current_row][current_col]);
		}
		printf("\n");
	}
}

void print_matrix_to_file(const matrix* matrix_to_save, FILE* output_file) {
	if (!matrix_to_save || !output_file) return;

	fprintf(output_file, "%d %d\n", matrix_to_save->rows, matrix_to_save->cols);

	for (int row = 0; row < matrix_to_save->rows; row++) {
		for (int col = 0; col < matrix_to_save->cols; col++) {
			fprintf(output_file, "%.6f ", matrix_to_save->data[row][col]);
		}
		fprintf(output_file, "\n");
	}
}

void fprintf_matrix(FILE* output_stream, const matrix* matrix_to_format,
	const char* format_string) {

	if (!output_stream || !matrix_to_format || !format_string) return;

	for (int row_idx = 0; row_idx < matrix_to_format->rows; row_idx++) {
		for (int col_idx = 0; col_idx < matrix_to_format->cols; col_idx++) {
			fprintf(output_stream, format_string,
			matrix_to_format->data[row_idx][row_idx]);
		}
		fprintf(output_stream, "\n");
	}
}
