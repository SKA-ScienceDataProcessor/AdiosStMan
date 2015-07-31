#!/bin/bash

QUOTA="5000000000" # in KB
OUTPUT="$SCRATCH/tmp"
writeBufSize=28000


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
            CHECK=$(du -s $OUTPUT | cut -f1)
            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $OUTPUT, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $OUTPUT/*
            fi

            if [ "$VENDOR" == "cray" ]; then
                NP=$(wc -l $PBS_NODEFILE | awk '{print $1}')
                echo "Total CPU count = $NP"
                RUN="aprun -n$NP -N1"
            else
                RUN="mpirun"
            fi

            RUNLINE="$RUN $JOBDIR/parallel_array_write $rows $length $length $OUTPUT/${rows}rows_${length}length_${JOBID}_${i}.casa $writeBufSize"
            echo $RUNLINE
            $RUNLINE >> $JOBDIR/log
        done
    done
done

