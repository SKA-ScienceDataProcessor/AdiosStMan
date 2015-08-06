#!/bin/bash
if [ "$VENDOR" == "cray" ]; then
    aprun -n1 -N1 $SLURM_SUBMIT_DIR/ms_read_column $DATADIR/chiles_original.ms $DATADIR/chiles_adios_agg.ms
else
    mpirun ${PBS_O_WORKDIR}/ms_read_column $DATADIR/chiles_original.ms $DATADIR/chiles_adios_agg.ms
fi



