# Macros are defined below
SHELL = /bin/sh
CFLAG = -Wall -g 
OMP = -fopenmp
CC = clang-omp
MPI = mpicc

all: TT_connected_partition.c
	${CC} ${OMP} -o ./temp TT_connected_partition.c -O1 -w	

clean:
	rm mp mpi ser

