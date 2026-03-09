#ifndef PARAMS_H
#define PARAMS_H

#include "func.h"

/* Total number of Monte Carlo samples. */
#define N 10000000ULL
/* Number of dimensions in the integration domain. */
#define DIM 20
/* Lower bound for each coordinate. */
#define LOWER_BOUND -1
/* Upper bound for each coordinate. */
#define UPPER_BOUND 1

/* Integrand function used by sequential and parallel executables. */
extern func_t F;

#endif
