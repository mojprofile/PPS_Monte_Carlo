CC := gcc
MPICC := mpicc
CFLAGS := -Wall -Werror -std=c99
LDFLAG := -lm
OBJ := n_gaussian.o uniform_rand.o config.o


all: sekvential parallel


sekvential: sekvential.o $(OBJ)
	$(CC) $(CFLAGS) -o sekvential sekvential.o $(OBJ) $(LDFLAG)

sekvential.o: sekvential.c config.h utils.h
	$(CC) $(CFLAGS) -c sekvential.c


parallel: parallel.o $(OBJ) 
	$(MPICC) $(CFLAGS) -o parallel parallel.o $(OBJ) $(LDFLAG)

parallel.o: parallel.c config.h utils.h
	$(MPICC) $(CFLAGS) -c parallel.c


n_gaussian.o: n_gaussian.c func.h
	$(CC) $(CFLAGS) -c n_gaussian.c

uniform_rand.o: uniform_rand.c utils.h
	$(CC) $(CFLAGS) -c uniform_rand.c

config.o: config.c config.h func.h
	$(CC) $(CFLAGS) -c config.c


clean:
	rm -f *.o parallel sekvential
