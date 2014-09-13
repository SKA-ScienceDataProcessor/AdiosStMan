#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PBS_O_WORKDIR

QUOTA="2000000000000"
prefix=/scratch/partner766/jwang/osd8

for rows in {1000..6000..200}
do
	for length in {2000..2000..200}
	do

		for i in {1..10}
		do
			CHECK=$(du -sb $prefix | cut -f1)

			if [ "$CHECK" -gt "$QUOTA" ]; then
				echo "$CHECK bytes in $prefix, reaching disk quota $QUOTA, cleaning up ..."
				rm -rf $prefix/*
			fi

			mpirun $PBS_O_WORKDIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${PBS_JOBID}_${i}.casa  >> $PBS_O_WORKDIR/log

		done

	done
done


