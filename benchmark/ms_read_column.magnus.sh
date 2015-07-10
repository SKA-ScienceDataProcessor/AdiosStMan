#!/bin/sh 


for i in $(seq 10 10 100)
do
	sbatch --account=$IVEC_PROJECT --time=00:30:00 --nodes=$i --ntasks-per-node=1 --dependency=singleton ms_read_column.sh
done




