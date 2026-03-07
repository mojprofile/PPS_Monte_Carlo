#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mpi.h>

#include "config.h"
#include "utils.h"


int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank + 45);

    uint64_t local_N = N / size;
    uint64_t quet = N % size;
    if (quet > 0 && rank == 0) local_N += quet;
    double local_sum, total_sum;
    double* x = malloc(DIM * sizeof(double));
    if (x == NULL) {
        MPI_Finalize();
        return 1;
    }

    local_sum = 0.0;
    for (uint64_t i = 0; i < local_N; i++) {
        for (uint64_t j = 0; j < DIM; j++) {
            x[j] = uniform_rand(LOWER_BOUND, UPPER_BOUND);
        }
        local_sum += F(x, DIM);
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double integral = (total_sum/N);
        for (uint64_t i = 0; i < DIM; i++) {
            integral *= UPPER_BOUND - LOWER_BOUND;
        }
        printf("Monte Carlo result: %.8f\n", integral);
    }

    free(x);
    MPI_Finalize();
    return 0;
}