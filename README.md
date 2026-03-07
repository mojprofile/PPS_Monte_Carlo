# Monte Carlo Integration (C + MPI)

This project estimates an N-dimensional Gaussian integral using the Monte Carlo method.
It includes:
- a sequential version (`sekvential`)
- a parallel MPI version (`parallel`)

## Requirements

- `gcc`
- `mpicc`
- `make`
- MPI runtime (for example OpenMPI or MPICH)

## Build

```bash
make all
```

## Run

Sequential:

```bash
./sekvential
```

Parallel (example with 4 processes):

```bash
mpirun -np 4 ./parallel
```

## Clean

```bash
make clean
```

## Configuration

Main parameters are defined in `config.h`:
- `N` (number of samples)
- `DIM` (dimension)
- `LOWER_BOUND`, `UPPER_BOUND` (integration range)
