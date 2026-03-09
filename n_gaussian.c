#include <math.h>

#include "func.h"


double compute_n_gaussian(double x[], size_t dim)
{
    /* Compute ||x||^2 = x_1^2 + ... + x_dim^2 for the Gaussian exponent. */
    double sum = 0.0;
    for (size_t i = 0; i < dim; i++) {
        sum += x[i] * x[i];
    }

    /* Evaluate normalized N-D Gaussian:
       f(x) = (2*pi)^(-dim/2) * exp(-||x||^2 / 2). */
    double norm_coeff = pow(2.0 * acos(-1.0), -((double)dim)/2.0);
    double exponent = -0.5 * sum;

    return norm_coeff * exp(exponent);
}
