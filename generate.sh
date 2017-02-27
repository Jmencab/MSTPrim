#!/bin/sh

for d in 0 2 3 4
do
	rm results/dim$d.txt
done

for N in 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072
do
	for D in 0 2 3 4
	do
		echo $N $D
		./randmst 8 $N 5 $D >> results/dim$D.txt
		sleep 1
	done
done