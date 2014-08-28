#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PBS_O_WORKDIR

SIZE="1000000000000"
prefix=/scratch/partner766/jwang

for rows in {200..4000..200}
do
	for length in {200..4000..200}
	do

		CHECK=$(du -sb $prefix | cut -f1)

		if [ "$CHECK" -gt "$SIZE" ]; then
			echo "$CHECK bytes in $prefix, reaching disk quota $SIZE, cleaning up ..."
			rm -rf $prefix/*
		fi

		mpirun $PBS_O_WORKDIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${PBS_JOBID}.casa  >> $PBS_O_WORKDIR/log

	done
done


