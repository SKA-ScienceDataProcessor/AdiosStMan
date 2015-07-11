#!/bin/bash
if [ "$JOBSCHEDULER" == "slurm" ]; then
    aprun -B $SLURM_SUBMIT_DIR/ms_read_column $scratch/chiles_original.ms $scratch/chiles_adios.ms
fi

if [ "$JOBSCHEDULER" == "pbs" ]; then
    mpirun ${PBS_O_WORKDIR}/ms_read_column $scratch/chiles_original.ms $scratch/chiles_adios.ms
fi



