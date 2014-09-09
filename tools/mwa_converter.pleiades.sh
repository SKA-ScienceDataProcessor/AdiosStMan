#!/bin/bash
#PBS -l walltime=12:00:00
#PBS -l nodes=1:ppn=12
#PBS -l mem=70gb

/home/jason/adiosStMan/tools/mwa_converter /scratch/jason/1067892840_tsm.ms /scratch/jason/1067892840_adios.ms 

