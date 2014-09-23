#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PBS_O_WORKDIR

QUOTA="2000000000000"
prefix=$scratch
JOBSCHEDULER="slurm"

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

			if [$JOBSCHEDULER -eq "slurm" ]; then
				aprun $SLURM_SUBMIT_DIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${SLURM_JOBID}_${i}.casa  >> $SLURM_SUBMIT_DIR/log
			fi

			if [$JOBSCHEDULER -eq "pbs" ]; then
				mpirun $PBS_O_WORKDIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${PBS_JOBID}_${i}.casa  >> $PBS_O_WORKDIR/log
			fi

		done

	done
done


