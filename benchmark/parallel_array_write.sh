#!/bin/bash

QUOTA="5000000000" # in KB
OUTPUT=$scratch/tmp

if [ "$VENDOR" == "cray" ]; then
    RUN="aprun -B"
else
    RUN="mpirun"
fi

if [ "$JOBSCHEDULER" == "slurm" ]; then
    JOBID=$SLURM_JOBID
    JOBDIR=$SLURM_SUBMIT_DIR
else
    JOBID=$PBS_JOBID
    JOBDIR=$PBS_O_WORKDIR
fi


for i in $(seq 1 10)
do
    for rows in $(seq 100 100 1000)
    do
        for length in $(seq 1000 1000 20000)
        do
            echo $rows $length $length $OUTPUT/${rows}rows_${length}length_${SLURM_JOBID}_${i}.casa
            CHECK=$(du -s $OUTPUT | cut -f1)
            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $OUTPUT, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $OUTPUT/*
            fi
                $RUN $JOBDIR/parallel_array_write $rows $length $length $OUTPUT/${rows}rows_${length}length_${JOBID}_${i}.casa  >> $JOBDIR/log
        done
    done
done

