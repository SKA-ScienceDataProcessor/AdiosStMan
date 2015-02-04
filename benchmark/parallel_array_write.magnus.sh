#!/bin/sh 

JOBSCHEDULER="slurm"

for i in $(seq 100 -10 1)
do
	sbatch --account=$project --time=12:00:00 --nodes=$i --ntasks-per-node=24 --dependency=singleton parallel_array_write.sh
done

for i in $(seq 10 -1 1)
do
	sbatch --account=$project --time=12:00:00 --nodes=$i --ntasks-per-node=24 --dependency=singleton parallel_array_write.sh
done





