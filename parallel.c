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
    /* local_sum: contribution of one rank, total_sum: sum on root after reduce. */
    double local_sum = 0.0, total_sum = 0.0;
    /* Reusable coordinate buffer for one DIM-dimensional sample point. */
    double* x = malloc(DIM * sizeof(double));
    if (x == NULL) {
        return 1;
    }

    /* Initialize MPI and query this process id (rank) and world size. */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Mix rank into seed so each process gets a different random stream. */
    srand((unsigned int)time(NULL) ^ (rank * 1337));

    /* Balanced work split:
       each rank gets floor(N/size), first (N%size) ranks get one extra. */
    local_N = N / size;
    quet = N % size;
    if (rank < quet) {
        local_N++;
    }

    /* Local Monte Carlo phase on each rank:
       sample local_N points and accumulate f(x) into local_sum. */
    for (uint64_t i = 0; i < local_N; i++) {
        for (size_t j = 0; j < DIM; j++) {
            x[j] = uniform_rand(LOWER_BOUND, UPPER_BOUND);
        }
        local_sum += F(x, DIM);
    }

    /* Global reduction (sum) to rank 0. */
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        /* Root converts global mean into integral:
           integral = (total_sum / N) * volume(domain). */
        double integral = total_sum / N;
        for (size_t i = 0; i < DIM; i++) {
            integral *= UPPER_BOUND - LOWER_BOUND;
        }
        printf("Monte Carlo result: %.8f\n", integral);
    }

    /* Release MPI resources and local allocations. */
    MPI_Finalize();
    free(x);
    return 0;
}
