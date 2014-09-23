#!/bin/sh 

for i in {1..6}
do
	for j in {1..1}
	do
		sbatch --account=$project --time=12:00:00 --nodes=$i --ntasks-per-node=24 --dependency=singleton parallel_array_write.sh
	done
done

