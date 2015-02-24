#!/bin/sh 

for i in $(seq 1 1 9)
do
	sbatch --account=$PROJECT --time=12:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton parallel_array_write.sh
done

for i in $(seq 10 10 100)
do
	sbatch --account=$PROJECT --time=12:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton parallel_array_write.sh
done



