#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "config.h"
#include "utils.h"


int main(int argc, char* argv[])
{   
    /* Running sum of f(x) over all generated samples. */
    double total_sum = 0.0;
    /* Temporary point in DIM-dimensional space reused each iteration. */
    double* x = malloc(DIM * sizeof(double));
    if (x == NULL) {
        return 1;
    }

    /* Seed pseudo-random generator once for this process. */
    srand(time(NULL));

    /* Monte Carlo sampling:
       1) draw x uniformly in [LOWER_BOUND, UPPER_BOUND]^DIM
       2) evaluate f(x)
       3) accumulate into total_sum */
    for (uint64_t i = 0; i < N; i++) {
        for (int j = 0; j < DIM; j++) {
            x[j] = uniform_rand(LOWER_BOUND, UPPER_BOUND);
        }
        total_sum += F(x, DIM);
    }

    /* Estimate integral as mean(f) * volume(domain).
       For a hypercube, volume = (UPPER_BOUND - LOWER_BOUND)^DIM. */
    double integral = total_sum / N;
    for (uint64_t i = 0; i < DIM; i++) {
        integral *= UPPER_BOUND - LOWER_BOUND;
    }

    printf("Monte Carlo result: %.8f\n", integral);
    free(x);
    return 0;
}
