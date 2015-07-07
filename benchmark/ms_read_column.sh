#!/bin/bash
mpirun -np 3 ${PBS_O_WORKDIR}/ms_read_column /scratch/jason/chiles_original.ms /scratch/jason/chiles_adios.ms
