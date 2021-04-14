CC=mpixlc
FLAGS=-Wall -pedantic -Wextra -Wno-unused-variable
PAR=-np 10

all:
	$(CC) redblack_2d_mpi.c -o out;

run:
	mpisubmit.bg -np 2 --stdout res_block/2.out out;
	mpisubmit.bg -np 4 --stdout res_block/4.out out;
	mpisubmit.bg -np 8 --stdout res_block/8.out out;
	mpisubmit.bg -np 16 --stdout res_block/16.out out;
	mpisubmit.bg -np 32 --stdout res_block/32.out out;
	mpisubmit.bg -np 64 --stdout res_block/64.out out;
	mpisubmit.bg -np 128 --stdout res_block/128.out out; 
cat:
	cat res_block/2.out;
	cat res_block/4.out;
	cat res_block/8.out;
	cat res_block/16.out;
	cat res_block/32.out;
	cat res_block/64.out;
	cat res_block/128.out; 
