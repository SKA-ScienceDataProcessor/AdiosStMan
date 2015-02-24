#!/bin/bash

jobid=""

for i in {1..9}
do
	jobid_last=$jobid
	jobid=$(qsub -W group_list=$PROJECT -q workq -l walltime=23:00:00,select=${i}:ncpus=12:mem=68gb:mpiprocs=1 -W depend=afterany:${jobid} parallel_array_write.sh)
	echo $jobid submitted with dependency $jobid_last
done


for i in {10..90..10}
do
	jobid_last=$jobid
	jobid=$(qsub -W group_list=$PROJECT -q workq -l walltime=23:00:00,select=${i}:ncpus=12:mem=68gb:mpiprocs=1 -W depend=afterany:${jobid} parallel_array_write.sh)
	echo $jobid submitted with dependency $jobid_last
done
