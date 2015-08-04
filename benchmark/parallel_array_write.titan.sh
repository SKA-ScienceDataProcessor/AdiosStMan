#!/bin/bash

jobid=""


for i in $(seq 1 1 9)
do
    jobid_last=$jobid
    if [ "$jobid" == "" ]; then
        jobid=$(qsub -A $PROJECT_ID -l walltime=2:00:00,nodes=${i} parallel_array_write.sh)
    else
        jobid=$(qsub -A $PROJECT_ID -l walltime=2:00:00,nodes=${i} -W depend=afterany:${jobid} parallel_array_write.sh)
    fi
    echo $jobid submitted with dependency $jobid_last
done


for i in $(seq 10 10 200)
do
    jobid_last=$jobid
    if [ "$jobid" == "" ]; then
        jobid=$(qsub -A $PROJECT_ID -l walltime=2:00:00,nodes=${i} parallel_array_write.sh)
    else
        jobid=$(qsub -A $PROJECT_ID -l walltime=2:00:00,nodes=${i} -W depend=afterany:${jobid} parallel_array_write.sh)
    fi
    echo $jobid submitted with dependency $jobid_last
done
