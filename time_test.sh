#!/usr/bin/env bash

set -euo pipefail

PARALLEL_BIN="parallel"
SEQUENTIAL_BIN="sequential"
MODE="${1:-both}"
PROC_COUNT="${2:-4}"

usage() {
    echo "Usage:"
    echo "  ./time_test.sh [sequential|parallel|both] [process_count]"
    echo
    echo "Examples:"
    echo "  ./time_test.sh sequential"
    echo "  ./time_test.sh parallel 8"
    echo "  ./time_test.sh both 4"
}

build_if_missing() {
    if [ ! -f "$PARALLEL_BIN" ] || [ ! -f "$SEQUENTIAL_BIN" ]; then
        make all > /dev/null 2>&1
    fi
}

run_sequential() {
    echo "Testing sequential version:"
    time ./"$SEQUENTIAL_BIN"
}

run_parallel() {
    echo "Testing parallel version (${PROC_COUNT} processes):"
    time mpirun -np "$PROC_COUNT" ./"$PARALLEL_BIN"
}

build_if_missing

case "$MODE" in
    sequential)
        run_sequential
        ;;
    parallel)
        run_parallel
        ;;
    both)
        run_sequential
        echo
        run_parallel
        ;;
    -h|--help|help)
        usage
        exit 0
        ;;
    *)
        echo "Unknown mode: $MODE"
        usage
        exit 1
        ;;
esac
