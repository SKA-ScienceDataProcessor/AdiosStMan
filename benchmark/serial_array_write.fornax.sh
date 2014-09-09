#!/bin/bash
#PBS -W group_list=partner766
#PBS -q workq
#PBS -l walltime=23:00:00
#PBS -l select=1:ncpus=12:mem=68gb:mpiprocs=1


cd $PBS_O_WORKDIR

python runbench.py

