#!/bin/bash

jobid=""

for i in {1..9}
do
    jobid_last=$jobid
    jobid=$(qsub -A $PROJECT_ID -l walltime=2:00:00,select=${i}:ncpus=1:mpiprocs=1 -W depend=afterany:${jobid} parallel_array_write.sh)
    echo $jobid submitted with dependency $jobid_last
done


