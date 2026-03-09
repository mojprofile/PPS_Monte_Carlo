#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "config.h"
#include "utils.h"


int main(int argc, char* argv[])
{   
    double total_sum = 0.0;
    double* x = malloc(DIM * sizeof(double));
    if (x == NULL) {
        return 1;
    }

    srand(time(NULL));

    for (uint64_t i = 0; i < N; i++) {
        for (int j = 0; j < DIM; j++) {
            x[j] = uniform_rand(LOWER_BOUND, UPPER_BOUND);
        }
        total_sum += F(x, DIM);
    }

    double integral = total_sum / N;
    for (uint64_t i = 0; i < DIM; i++) {
        integral *= UPPER_BOUND - LOWER_BOUND;
    }

    printf("Monte Carlo result: %.8f\n", integral);
    free(x);
    return 0;
}
