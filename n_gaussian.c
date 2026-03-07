#include <math.h>

#include "func.h"


double compute_n_gaussian(double x[], size_t dim)
{
    double sum = 0.0;
    for (size_t i = 0; i < dim; i++) {
        sum += x[i]*x[i];
    }
    return exp(-sum);
}
