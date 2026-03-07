#ifndef FUNC_H
#define FUNC_H

#include <stddef.h>

typedef double (*func_t)(double[], size_t);

double compute_n_gaussian(double x[], size_t dim);

#endif