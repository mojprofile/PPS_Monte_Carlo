PARALLEL="parallel"
SEKVENTIAL="sekvential"
P_COUNT=$1

if [  ! -f "$PARALLEL"  ] || [  ! -f "$SEKVENTIAL"  ]; then
    make all > /dev/null 2>&1
fi

echo "test sekvential version:"
time ./"$SEKVENTIAL"

echo

echo "test parallel version"
time mpirun -np "$P_COUNT" ./"$PARALLEL"


make clean > /dev/null 2>&1
