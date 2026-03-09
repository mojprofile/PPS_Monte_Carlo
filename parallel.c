#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <mpi.h>

#include "config.h"
#include "utils.h"


int main(int argc, char* argv[])
{
    int rank, size;
    uint64_t local_N, quet;
    double local_sum = 0.0, total_sum = 0.0;
    double* x = malloc(DIM * sizeof(double));
    if (x == NULL) {
        return 1;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand((unsigned int)time(NULL) ^ (rank * 1337));

    local_N = N / size;
    quet = N % size;
    if (rank < quet) {
        local_N++;
    }

    for (uint64_t i = 0; i < local_N; i++) {
        for (size_t j = 0; j < DIM; j++) {
            x[j] = uniform_rand(LOWER_BOUND, UPPER_BOUND);
        }
        local_sum += F(x, DIM);
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double integral = total_sum / N;
        for (size_t i = 0; i < DIM; i++) {
            integral *= UPPER_BOUND - LOWER_BOUND;
        }
        printf("Monte Carlo result: %.8f\n", integral);
    }

    MPI_Finalize();
    free(x);
    return 0;
}