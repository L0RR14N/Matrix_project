#ifndef OUTPUT_H
#define OUTPUT_H

#include "../matrix/matrix.h"
#include <stdio.h>

void print_matrix(const matrix* matrix);
void print_matrix_to_file(const matrix* matrix, FILE* file);

void fprintf_matrix(FILE* stream, const matrix* matrix, const char* fmt);

#endif
