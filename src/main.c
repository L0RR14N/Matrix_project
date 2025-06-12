#include "../include/matrix/matrix.h"
#include "../include/output/output.h"
#include <stdio.h>

int main() {
	printf("Starting program...\n");

	matrix* A = load_matrix_from_file("../data/A.txt");
	if(!A) printf("[ERROR] Failed to load A.txt\n");
	matrix* B = load_matrix_from_file("../data/B.txt");
	if(!B) printf("[ERROR] Failed to load B.txt\n");
	matrix* C = load_matrix_from_file("../data/C.txt");
	if(!C) printf("[ERROR] Failed to load C.txt\n");
	matrix* D = load_matrix_from_file("../data/D.txt");
	if(!D) printf("[ERROR] Failed to load D.txt\n");

	if (!A || !B || !C || !D) {
		printf("[CRITITCAL ERROR] One or more matricies failed to load. Terminating program\n");
		return 1;
	}

	matrix* AB = multiply_matrices(A, B);
	matrix* AB_minus_C = subtract_matrices(AB, C);
	matrix* D_transposed = transpose_matrix(D);
	matrix* result = add_matrices(AB_minus_C, D_transposed);

	if (!result) {
		fprintf(stderr, "[COMPUTATION ERROR] Failed to compute final result\n");
	} else {
		printf("Result:\n");
		print_matrix(result);

		save_matrix_to_file(result, "data/result.txt");
	}

	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(D);
	free_matrix(AB);
	free_matrix(AB_minus_C);
	free_matrix(D_transposed);
	free_matrix(result);

	return 0;
}
