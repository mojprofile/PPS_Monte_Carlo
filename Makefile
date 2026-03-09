CC := gcc
MPICC := mpicc
CFLAGS := -O2 -Wall -Werror -std=c99
LDFLAG := -lm
OBJ := n_gaussian.o uniform_rand.o config.o


all: sequential parallel


sequential: sequential.o $(OBJ)
	$(CC) $(CFLAGS) -o sequential sequential.o $(OBJ) $(LDFLAG)

sequential.o: sequential.c config.h utils.h
	$(CC) $(CFLAGS) -c sequential.c


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
	rm -f *.o perf* gmon* cachegrind* massif* callgrind* parallel sequential
