#!/bin/sh 

for i in $(seq 1 1 10)
do
    qsub -A $PROJECT_ID -l walltime=00:10:00,nodes=${i} ms_read_column.sh
done





