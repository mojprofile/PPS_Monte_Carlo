# Monte Carlo Integration (C + MPI)

This project estimates an N-dimensional Gaussian integral using the Monte Carlo method.
It includes:
- a sequential version (`sequential`)
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
./sequential
```

Parallel (example with 4 processes):

```bash
mpirun -np 4 ./parallel
```

## Timing Script

Use `time_test.sh` to measure runtime for sequential, parallel, or both versions.

Show help:

```bash
./time_test.sh --help
```

Run only sequential:

```bash
./time_test.sh sequential
```

Run only parallel with 8 processes:

```bash
./time_test.sh parallel 8
```

Run both (default parallel process count is 4):

```bash
./time_test.sh both
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
