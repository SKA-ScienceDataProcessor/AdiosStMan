#!/bin/bash 

export VENDOR = "Tianhe2"

for i in $(seq 500 -100 100)
do
	yhbatch -N $i -n $i --dependency=singleton parallel_array_write.sh $i $i
done

for i in $(seq 90 -10 10)
do
        yhbatch -N $i -n $i --dependency=singleton parallel_array_write.sh $i $i
done




