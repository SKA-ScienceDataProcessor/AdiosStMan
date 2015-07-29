#!/bin/sh 

for i in $(seq 1 1 10)
do
	sbatch --account=$IVEC_PROJECT --time=01:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton ms_read_column.sh
done

for i in $(seq 10 10 100)
do
	sbatch --account=$IVEC_PROJECT --time=05:00:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton ms_read_column.sh
done




