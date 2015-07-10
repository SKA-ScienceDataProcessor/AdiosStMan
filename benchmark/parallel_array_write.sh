#!/bin/bash

QUOTA="5000000000" # in KB
prefix=$scratch/stripe1

for i in $(seq 1 10)
do
    for rows in $(seq 100 100 1000) 
    do
        for length in $(seq 1000 1000 20000)
        do


            echo $rows $length $length $prefix/${rows}rows_${length}length_${SLURM_JOBID}_${i}.casa

            CHECK=$(du -s $prefix | cut -f1)

            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $prefix, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $prefix/*
            fi

            if [ "$JOBSCHEDULER" == "slurm" ]; then
                aprun -B $SLURM_SUBMIT_DIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${SLURM_JOBID}_${i}.casa  >> $SLURM_SUBMIT_DIR/log
            fi

            if [ "$JOBSCHEDULER" == "pbs" ]; then
                mpirun $PBS_O_WORKDIR/parallel_array_write $rows $length $length $prefix/${rows}rows_${length}length_${PBS_JOBID}_${i}.casa  >> $PBS_O_WORKDIR/log
            fi


        done

    done
done


