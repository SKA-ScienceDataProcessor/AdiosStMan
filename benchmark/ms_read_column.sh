#!/bin/bash

if [ "$JOBSCHEDULER" == "slurm" ]; then
    JOBID=$SLURM_JOBID
    JOBDIR=$SLURM_SUBMIT_DIR
else
    JOBID=$PBS_JOBID
    JOBDIR=$PBS_O_WORKDIR
fi

if [ "$VENDOR" == "cray" ]; then
    aprun -n1 -N1 $JOBDIR/ms_read_column $DATADIR/chiles_original.ms $DATADIR/chiles_adios_agg.ms
else
    mpirun $JOBDIR/ms_read_column $DATADIR/chiles_original.ms $DATADIR/chiles_adios_agg.ms
fi



