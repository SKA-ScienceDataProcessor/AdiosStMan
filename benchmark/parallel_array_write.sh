#!/bin/bash --login

#. /lustre/atlas2/csc143/proj-shared/ska/ska_bashrc.sh

source /home/blao/bashrc_AdiosStMan

QUOTA="5000000000" # in KB
OUTPUT="/scratch/pawsey0129/AdiosStMan/data1"

writeBufRows=10

if [ "$JOBSCHEDULER" == "slurm" ]; then
    JOBID=$SLURM_JOBID
#    JOBDIR=$SLURM_SUBMIT_DIR
else
    JOBID=$PBS_JOBID
#    JOBDIR=$PBS_O_WORKDIR
fi

JOBDIR="/home/blao/AdiosStMan_u2/AdiosStMan/benchmark"


for i in $(seq 1 1)
do
    for rows in $(seq 1000 200 1000)
    do
        for length in $(seq 9000 1000 9000)
        do
            CHECK=$(du -s $OUTPUT | cut -f1)
            if [ "$CHECK" -gt "$QUOTA" ]; then
                echo "$CHECK bytes in $OUTPUT, reaching disk quota $QUOTA, cleaning up ..."
                rm -rf $OUTPUT/*
            fi

            if [ "$VENDOR" == "cray" ]; then
                NP=$(wc -l $PBS_NODEFILE | awk '{print $1}')
                RUN="aprun -B"
            else
                RUN="mpirun"
            fi

            RUNLINE="$RUN $JOBDIR/parallel_array_write $rows $length $length $OUTPUT/${rows}rows_${length}length_${i}.casa $writeBufRows"
            echo $RUNLINE
            $RUNLINE >> $JOBDIR/log
        done
    done
done

